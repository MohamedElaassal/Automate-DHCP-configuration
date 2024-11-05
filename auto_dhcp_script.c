#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

void calculate_network_and_broadcast(const char *ip_address, int prefix, char *network, char *broadcast) {
    struct in_addr ip, netmask, network_ip, broadcast_ip;

    // Convert IP address to binary form
    inet_aton(ip_address, &ip);

    // Calculate netmask from CIDR prefix
    netmask.s_addr = htonl(~((1 << (32 - prefix)) - 1));

    // Calculate network address
    network_ip.s_addr = ip.s_addr & netmask.s_addr;
    inet_ntop(AF_INET, &network_ip, network, INET_ADDRSTRLEN);

    // Calculate broadcast address
    broadcast_ip.s_addr = network_ip.s_addr | ~netmask.s_addr;
    inet_ntop(AF_INET, &broadcast_ip, broadcast, INET_ADDRSTRLEN);
}

int main() {
    char nic_name[50];
    char dhcp_ip[50];
    int prefix;
    char gateway[50];
    char range_start[50];
    char range_end[50];
    int default_lease_time;
    int max_lease_time;

    // Prompt user for NIC details and IP addresses
    printf("Enter the network interface name (e.g., eth0): ");
    fgets(nic_name, sizeof(nic_name), stdin);

    // Remove trailing newline from nic_name if present
    size_t len = strlen(nic_name);
    if (len > 0 && nic_name[len - 1] == '\n') {
        nic_name[len - 1] = '\0';
    }

    printf("Enter the static IP address for the DHCP server (e.g., 192.168.1.2): ");
    scanf(" %[^\n]", dhcp_ip);

    printf("Enter the prefix length (CIDR notation, e.g., 24): ");
    scanf(" %d", &prefix);

    printf("Enter the gateway IP address (e.g., 192.168.1.1): ");
    scanf(" %[^\n]", gateway);

    printf("Enter the DHCP range start IP (e.g., 192.168.1.11): ");
    scanf(" %[^\n]", range_start);

    printf("Enter the DHCP range end IP (e.g., 192.168.1.254): ");
    scanf(" %[^\n]", range_end);

    printf("Enter the default lease time in seconds (e.g., 3600): ");
    scanf(" %d", &default_lease_time);

    printf("Enter the max lease time in seconds (e.g., 7200): ");
    scanf(" %d", &max_lease_time);

    // Calculate network address and broadcast address
    char network[INET_ADDRSTRLEN];
    char broadcast[INET_ADDRSTRLEN];
    calculate_network_and_broadcast(dhcp_ip, prefix, network, broadcast);

    // Step 1: Install DHCP server
    printf("Installing DHCP server...\n");
    system("sudo dnf install -y dhcp-server");

    // Step 2: Configure static IP, gateway, and manual method using nmcli
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "sudo nmcli con mod \"%s\" ipv4.addresses %s/%d && "
        "sudo nmcli con mod \"%s\" ipv4.gateway %s && "
        "sudo nmcli con mod \"%s\" ipv4.method manual && "
        "sudo nmcli con down \"%s\" && "
        "sudo nmcli con up \"%s\"",
        nic_name, dhcp_ip, prefix,
        nic_name, gateway,
        nic_name,
        nic_name,
        nic_name);

    // Execute the combined command
    int result = system(cmd);
    if (result != 0) {
        printf("An error occurred during network configuration.\n");
        return 1;
    }

    // Step 3: Configure DHCP in /etc/dhcp/dhcpd.conf
    printf("Configuring DHCP server in /etc/dhcp/dhcpd.conf...\n");
    snprintf(cmd, sizeof(cmd),
             "echo 'subnet %s netmask 255.255.255.0 {"
             "  range %s %s;"
             "  option routers %s;"
             "  option broadcast-address %s;"
             "  default-lease-time %d;"
             "  max-lease-time %d;}' | sudo tee -a /etc/dhcp/dhcpd.conf",
             network, range_start, range_end, gateway, broadcast, default_lease_time, max_lease_time);
    system(cmd);

    // Step 4: Restart and enable DHCP service
    printf("Starting and enabling DHCP server service...\n");
    system("sudo systemctl restart dhcpd.service");
    system("sudo systemctl enable dhcpd.service");

    printf("DHCP server configuration completed.\n");

    return 0;
}
