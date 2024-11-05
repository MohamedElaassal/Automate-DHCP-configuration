<h1>Automate-DHCP-Configuration</h1>

Automate-DHCP-Configuration is a script written in the C programming language that automates the entire process of configuring a DHCP server on a Linux server. Although Fedora is used as an example, understanding its workflow allows you to modify it to work with similar distributions, such as CentOS, Red Hat, and others.

<h2>Why was Automate-DHCP-Configuration developed?</h2>
This script simplifies the setup of a DHCP server in Linux environments, reducing the time and errors associated with manual configuration. It automates the process, making it quicker and easier to establish a reliable DHCP server on Fedora and similar distributions. Users can also modify the script for different Linux distributions, enhancing flexibility and saving time.

<h2>Functionalities</h2>

<h4>Automated Configuration</h4>
The script automates the entire setup process for a DHCP server, significantly reducing the time and potential errors involved in manual configuration.

<h4>Dynamic Input</h4>
Users are prompted to input essential parameters, including the network interface name, static IP address for the DHCP server, prefix length, gateway IP address, DHCP range, and lease times, making it customizable for various network setups.

<h4>Network and Broadcast Address Calculation</h4>
The script calculates the network and broadcast addresses based on the provided IP address and prefix length, ensuring correct subnetting for the DHCP configuration.

<h4>DHCP Server Installation</h4>
It automatically installs the DHCP server software using the package manager, making it easy to get started with the installation process.

<h4>Network Configuration</h4>
The script configures the network interface using `nmcli`, setting the static IP address, gateway, and changing the connection method to manual.

<h4>DHCP Configuration File Update</h4>
It appends the necessary subnet and option settings to the `/etc/dhcp/dhcpd.conf` configuration file, defining the DHCP range and lease times for clients.

<h4>Service Management</h4>
Finally, the script restarts and enables the DHCP service, ensuring that it runs on system startup.

<h2>Usage</h2>

If you have a Fedora Server Edition version 38 or higher and the `dnf` package manager, you shouldn't encounter any issues. It is recommended to keep the network interface card (NIC) set as NAT to avoid installation problems, as an internet connection is necessary to install the `dhcp-server` package.

Follow these steps to use the script:

1. Launch a terminal.
2. Compile and execute the code from the terminal with superuser privileges.
3. You can easily configure the DHCP server by entering the following parameters:
   - NIC name
   - IPv4 address to assign
   - Subnet prefix
   - Gateway IP address
   - DHCP range
   - Default lease time
   - Maximum lease time


