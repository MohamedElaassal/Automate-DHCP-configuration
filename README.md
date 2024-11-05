<h1>Automate-DHCP-Configuration</h1>

Automate-DHCP-Configuration is a script written in the C programming language that automates the entire process of configuring a DHCP server on a Linux server. Although Fedora is used as an example, understanding its workflow allows you to modify it to work with similar distributions, such as CentOS, Red Hat, and others.

<h2>Why was Automate-DHCP-Configuration developed?</h2>
This script was developed to simplify and streamline the process of setting up a DHCP server in Linux environments. Configuring a DHCP server manually can be time-consuming and prone to errors, particularly for users who are new to server administration or those managing multiple deployments. By automating the configuration process, this script makes it easier and faster to set up a reliable DHCP server on Fedora and other similar distributions. Users can also adapt the script to fit various Linux distributions, enhancing flexibility and saving time across different server environments.

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
