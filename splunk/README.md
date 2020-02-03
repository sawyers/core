# Splunk

Start up your work machines, `vagrant up` to start the vagrantfile

On windows you may need to disable hyper-v to use virtual box by going to windows features and disable it.

## What is splunk?

Used for system logs and machine data to collect, search, report, visualize, and alert

There is a free and paid version.

Simple keyword searching, advanced query syntax, stored reports, dashboards. ect.

Download from products / pricing and download splunk free (account required) [created and saved in 1password private vault]

(!) for this Vagrant setup you don't install splunk on your station, you install it in the splunk vm started by vagrant.

Click download the deb file, then cancel the download and use the "Useful Tools" wget command to download from inside the VN

When installed splunk will be running at 192.168.33.10:8000

```bash
vagrant ssh splunk
sudo su -
wget -O splunk-7.3.1-bd63e13aa157-linux-2.6-amd64.deb 'https://www.splunk.com/bin/splunk/DownloadActivityServlet?architecture=x86_64&platform=linux&version=7.3.1&product=splunk&filename=splunk-7.3.1-bd63e13aa157-linux-2.6-amd64.deb&wget=true'
dpkg -i splunk-7.3.1-bd63e13aa157-linux-2.6-amd64.deb
cd /opt/splunk/bin ; ./splunk start --accept-license
Do you agree with this license? [y/n]: y
Please enter an administrator username: admin
Please enter a new password: <my default password>
./splunk enable boot-start ; systemctl enable splunk ; systemctl start splunk
```

Using a browser go to http://192.168.33.10:8000 to sign into the splunk console

Lost your splunk app password?  https://splunkonbigdata.com/2018/09/15/how-to-reset-the-forgotten-password-of-admin-in-splunk/

add data; monitor [ a directory ]; /var/log/syslog

Splunk will detect the type (syslog) create the search and can take a bit to index things

Setup a non-admin user and password and assign it to the admin role

Switch user for safety and search 'boot'

## Adding apps

Adding apps requires the splunk.com logins and passwords

Adding Linux / Unix add on and configuring to harvest /var/log (via radio button config page), this causes it to auto index / harvest the new data source right away

Other apps like slack, aws, etc, are added in the same way

logging signal vs noise is vital to help with reports

alerts help with that so once you know something is important you should add it to alerts.

ex
sometimes the gets backed up and can sometimes cause the app to crash.

Too frequent alerts leads to ignored messages, so you should filtere out bellow a threshold.

## Practical exercises - Log files

log forwarding has several options, but common is universal forwarder
splunk -> settings -> forwarding / receiving, set a port to enable the splunk server to receive input.

each system that will ship data will need the forwardering agent installed on each machine.

https://www.splunk.com/en_us/download/universal-forwarder.html

```bash
vagrant ssh gitea
sudo su -
wget -O splunkforwarder-7.3.1-bd63e13aa157-linux-2.6-amd64.deb 'https://www.splunk.com/bin/splunk/DownloadActivityServlet?architecture=x86_64&platform=linux&version=7.3.1&product=universalforwarder&filename=splunkforwarder-7.3.1-bd63e13aa157-linux-2.6-amd64.deb&wget=true'
dpkg -i splunkforwarder-7.3.1-bd63e13aa157-linux-2.6-amd64.deb
cd /opt/splunkforwarder/bin ; ./splunk start --accept-license
<requires a login and password>
./splunk enable boot-start ; systemctl enable splunk ; systemctl start splunk
cd /opt/splunkforwarder/bin
./splunk add forward-server 192.168.33.10:9997
./splunk add monitor /var/log/
```

/opt/splunkforwarder/etc/system/local is the config file locations and good for configuration via automation

login prompt is for the forwarder, not the splunk server and is configured during the first splunk start from above.

That sends logs but doesn't monitor anything yet

If we use the same forwarder login / password we can copy the the encrypted password file and copy it around to automate things

https://answers.splunk.com/answers/268164/how-to-fully-automate-the-installation-and-configu.html

## Practical - UNix config

Enable settings you want in the linux add on then add the splunk addon for installing on each machine.

To put the add-ons to client nodes, you have to go from the splunk page and download the add on script and copy it to each monitored host.

then in /opt/splunkforwarder/etc/apps extract the downloaded app

This example is without template config, which would be part of automated install.

```bash
cd /opt/splunkforwarder/etc/apps/
tar xpvf <APP>
cd Splunk_TA_nix ; mkdir local
cp default/inputs.conf local
cd local ; edit inputs.conf
systemctl restart splunk
```

Setting this up for something like sierra should be pretty easy, but getting it for docker containers may be something else completely

https://www.splunk.com/blog/2015/08/24/collecting-docker-logs-and-stats-with-splunk.html

The JVM agent
https://splunkbase.splunk.com/app/1716/

Start by getting a stack setup then pull out datadog one at a time and replace it with a log forwarder going to splunk.iii.com

