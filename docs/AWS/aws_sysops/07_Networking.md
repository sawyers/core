# Networking
- [Networking](#networking)
  - [VPC Overview](#vpc-overview)
    - [Tips](#tips)
  - [Build Your Own Custom VPC - Part 1](#build-your-own-custom-vpc---part-1)
  - [Build Your Own Custom VPC - Part 2](#build-your-own-custom-vpc---part-2)
  - [Creating a NAT Instance](#creating-a-nat-instance)
    - [Tips](#tips-1)
  - [Network ACLs and Security Groups](#network-acls-and-security-groups)
    - [Tips](#tips-2)
  - [VPC Endpoints](#vpc-endpoints)
  - [VPC Flow Logs](#vpc-flow-logs)
    - [Tips](#tips-3)
  - [VPC CIDR Calculations](#vpc-cidr-calculations)
    - [Tips](#tips-4)
  - [AWS Direct Connect](#aws-direct-connect)
  - [VPC Summary](#vpc-summary)
  - [DNS 101](#dns-101)
    - [Tips](#tips-5)
  - [Register a Domain Name Lab](#register-a-domain-name-lab)
  - [Simple Routing Policy Lab](#simple-routing-policy-lab)
  - [Weighted Routing Policy Lab](#weighted-routing-policy-lab)
  - [Latency Routing Policy Lab](#latency-routing-policy-lab)
  - [Failover Routing Policy Lab](#failover-routing-policy-lab)
  - [Geolocation Routing Policy Lab](#geolocation-routing-policy-lab)
  - [Multivalue Answer Routing](#multivalue-answer-routing)
  - [DNS Exam Tips](#dns-exam-tips)
  - [Networking Quiz](#networking-quiz)
    - [Key](#key)
  
## VPC Overview

* A data center in the cloud
* Every region gets a default VPC
* Defined as a way to provision logically isolated section of AWS where you can launch resources in a virtual network you define
* You can configure as you like with public / private subnets and multiple layers of service like security groups and access control
* You can connect VPNs between corporate and VPC
* Connect via Internet Gateway or Virtual Private Gateway (for vpns)
* Sent through a router / route table
* Checks the network ACL
* reaches the requested subnet
* in the subnet there are security groups next 
* lastly connect to the instance requested
* 1 subnet to 1 AZ, no splitting a subnet across AZs
* Possible CIDRs are 10/8 or 172.16/12 or 192.168/16, in order of how many IP's you get.
* If you need more you can have at least 5 VPC's per region
* With VPC's you can launch instances into subnets of your choice
* Assign customer IP ranges / subnet
* Configure route tables between subnets
* Create internet gateways and attach it to the VPC (you only get 1)
* Better security control over resources like private subnets
* Instance security groups
* Subnet access control lists to block IP addresses
* Default VPC
  * You get a default in every region
  * All have a route to the internet
  * All EC2 get a public and private IP by default
* VPC Peering to connect VPCs
  * Allows connection from one VPC to another with direct network connect using private IP addresses
  * Instances behave as if they are on the same private network
  * You can peer VPCs to other accounts
  * Peering is in a star config, one central with 4 others
  * VPC b-d peer to vpc a, vpc b doesn't by default connect to vpc c

### Tips 

* logical data center
* consists of a gateway, route tables, ACL, subnets and security groups
* subnets don't span AZs
* Security groups are stateful; ACL are stateless
* No transitive peering
  
## Build Your Own Custom VPC - Part 1

* Start with the VPC console
* Create new with a name and CIDR
  * Creating that makes route table but no gateway
* Next make subnets in the VPC with name and CIDR range
  * Note you loose 5 IP's for overhead like DNS, router, etc.
* Make a second one, for redundancy and for public/private
* need an internet gateway to make it public, so make one and attach it.  Only one vpc doesn't have a gateway already so you only get one option
* Route table needs updated, one was created for you already but needs updated to associate the subnets. By default the route table has internet access which isn't best practice most of the time
* Create a new route table to address this
* In the NEW route add a route of 0.0.0.0/0 to the igw made earlier, do the same for IPv6
* Associate a subnet with the public route, the other will stay with the default that is private
* For custom VPC's you don't get auto assign public by default, so modify your public to allow it under actions for the public one
* Start 2 instance, one in each.
* One gets a public IP and can be SSH'd into, the other is private and can't
* The public also doesn't have a route to the private subnet, so you can't connect from there yet

## Build Your Own Custom VPC - Part 2

* Instead of changing the default and secure security group add a new one
* This security group defines several connections that are open the the subnet of the public subnet
* on the private server add it to the new SG
* Either forward the connection through the public to the private or copy the pem to the public
* While you can now connect to the private instance using forwarding you don't have outbound access from private to the internet

## Creating a NAT Instance

* Nat instances are going out but still get tested on.
* Launch a new instance from marketplace 
* Once started you don't need to log into it
* Attach a security group allowing internet access on http/https
* Disable source/destination checks on the nat instance
* Add a route for the nat. of everything target to nat
* If the NAT instance dies you are done, if the AZ errors you are done fragile and limited
* Better to use a NAT gateway
* From VPC create a new NAT gateway in the public subnet and update the route table to have the default table connect the internet through the NAT gateway
* NAT gateways have to be in each AZ for redundancy, but 1 will be fine for dev/test
* Now the private instances can route over to the NAT gateway in the public subnet to get to the internet
  
### Tips

* When creating NAT instances disable source checking
* NAT instances must be in a public subnet
* Must have a route out of the private subnet to the NAT instance
* Traffic limited depending on instance size, can be a bottleneck
* You can make them into ASG across AZ for HA
* Gateways are just better
* Auto scaled
* No patching / security groups, managed by AWS
* Always update route tables
* You should have redundant gateways in different AZ
* Gateways are more secure
* Gateways have a minor price from EIP
  
## Network ACLs and Security Groups

* VPC comes with a default ACL that allows all in by default
* A subnet can only have 1 acl attached
* Rules done per 100, so make a new one
* Any new ACL's are deny all so you have to add new rules, like HTTP, ssh, etc
* Since ALC's are stateless you have to add outbound as well, including ephereral ports, 1024-65535 to be pretty wide open
* Next associate that with your public subnet
* If you want you can start fine tuning the rules based on what you are doing. Rules are processed in number order, so if you want to say open http to everyone except some CIDR you have to have the deny before the allow.
* ACL's are done before security groups
  
### Tips

* Default ACL allows all traffic, new custom ones are deny all to start with
* The subnet has to be associated with the ACL to be used
* You can have an ACL to multiple subnets, but each subnet can only have one ACL
* ACL's are a number list of rules processed in counting order
* ACl's are stateless so you have seperate in and outbound traffic
* Make sure to allow outbound ephemeral ports
* You can block IP addresses with ACL, not security groups

## VPC Endpoints

* While NAT can work traffic is going to the internet instead of staying internal, it also means traffic is going through the NAT gateway when it doesn't need to
* So make an internal gateway as an endpoint
* Create a role for ec2 and give it s3 access
* Then in EC2 you can add a role to a running instance to add that role
* That allows the instance to use S3, but it still needs a route to it
* It could use NAT gateway but goes out to public, so an endpoint in the VPC keeps that traffic internal
* Add an endpoint and select the VPC
  * Pick the subnets to add
  * create
* Doing that adds the endpoint to the route table for the subnets picked
* Now using AWS services with an endpoint setup you keep the traffic internal to AWS without going out to the internet

## VPC Flow Logs

* They capture info about the IP traffic going in/out to network interfaces in the VPC and can be read using Cloudwatch
* We can create them at:
  * VPC level
  * Subnet level
  * Network interface level
* A role is needed for flow logs and is used when creating the flow logs.
* You need to use cloudwatch to create a log group
* Once you have the role and log group that's is it
* You can stream the logs to lambda to react to events or stream to elasticsearch

### Tips

* Can't enable on peered VPCs
* maybe can't tag it
* Once created you can't change it
* Not all traffic is monitored, DHCP, AWS DNS, AWS default Router
* Remember if this is for practice you should clean up resources or you will be billed for them

## VPC CIDR Calculations

* How to calculate the number of addresses in a CIDR.
* /24 == 256 each time you go up it cuts the count in half (256,128,64,32,16)
* subtract 5 from the value for overhead (251,123,59,27,11)

### Tips

* Max size for a subnet is /16
* Min size is /28
* Subtract 5 from possible
* Be able to give things like smallest subnet to fix X devices

## AWS Direct Connect

* Allows fast connection from local data center into the VPC via direct connect gateway with a route table to the gateway.
* Very similar to a NAT gateway
* Can cross VPC's even in different regions

## VPC Summary

* Built out VPC with public and private subnet
* Added NAT gateway for outbound to internet access via route table
* NAT instances disable source/dest check
  * Must be in public
  * Must have a route from private to nat instance
  * bottleneck
  * can be an ASG cross az
  * Behind security group
* NAT gateways are better in every way
  * Still needs a route
* Direct connect gateway to link your local data center to AWS
  * Can be cross region / VPC via route tables
* ACL
  * Comes with a default with all allowed
  * Custom ones start with deny all
  * Each subnet has an ACL
  * An ACL can have more than one subnet
  * It is stateless, so you set inbound AND outbound
  * Rules processed in counting order
  * Remember outbound ephemeral ports
  * ACL's can block IP address
* CIDR 
  * starting at /24 you get 256 addresses and cut in have till /28 at 16 IPs
  * That number subtract 5 for AWS overhead 251 to 11
* Flow logs track most network traffic including peered VPCs from the same account
  * AWS DNS, Windows licenses, metadata, DHCP and default VPC router is excluded
* VPC Endpoint
  * Allows traffic for AWS services like S3 to stay inside the AWS network rather than going out to the public network

## DNS 101

* Convert name to IP, either IPv4 or IPv6
* v4 could be running low at some point
* v6 is more or less forever
* Slowly moving to v6 over time
* Right most name of a DNS is the top level domain, .com, .edu
* Next most right is 2nd level domain
* Top level is run by IANA through registrars like godaddy or similar to be sure that all names are unique
* Route 53 (joke from route 66 but it works on port 53)
* DNS has SOA (start of authority)
  * Name of server that supplied the data
  * Admin
  * Version
  * TTL (in seconds)
* A records - most basic type of DNS record, translates name to address
* Cnames - resolve one domain name to another, like m.iii.com to mobile.iii.com, can't be used for naked domains
* Alias - map resources to ELB, CloudFront, S3. Map one DNS to another

### Tips

* Remember ELB's don't have default IPv4, you always use DNS, but you can use an alias record pointing to that DNS
* Alias can be used for naked domains but only for AWS resources
* SOA stores details about the setup
* Alias saves time by having R53 automatically point to the correct internal resolved address
* MX record (mail server)
* PTR reverse lookup

## Register a Domain Name Lab

* Go to Route 53 and register a domain if it is available
* Fill out contact info
* it can take a few days to fully register, or not.
* It will now be listed in hosted zones
* Costs ~$12 / year but can go up or down depending on the top level domain

## Simple Routing Policy Lab

* Simple you have one record with multiple addresses. R53 returns all addresses in a random order
  * www.example.com => [10.0.0.1, 10.0.0.2, 10.0.0.3], returns any of the 3 on lookup randomly
* Doesn't impact local cache so once you resolve within the TTL you will stay on that IP

## Weighted Routing Policy Lab

* Simple you have one record with multiple addresses and a preference of how important it is and an ID name. 
* R53 returns all addresses in that order
  * www.example.com => [10.0.0.1 -> 69, 10.0.0.2 -> 15, 10.0.0.3 -> 15], returns the first 2/3 of the time, the other are roughly even on the remaining 1/3
* Multiple records get added for the same name with different target IP, weight and ID
* Good for A-B testing or gradual cut over

## Latency Routing Policy Lab

* Similar as weighted but checks the IP's possible for speed relative to the customer
* Instead of setting a weight you set the region and have all IPs in that region

## Failover Routing Policy Lab

* Failover setup for active / passive setup for disaster recovery via health check in R53
* You do have to create the health check in r53, what to check, port, target, etc.
* If the primary goes unhealthy it will fail over to the secondary

## Geolocation Routing Policy Lab

* Provide a localized website based on your physical location to provide translated pages or to comply with things like GDPR
* Similar to latency based but different use case.

## Multivalue Answer Routing

Multiple record sets with health check but works mostly like simple.  
Make a record in R53 for each possible answer

Multi answer picks randomly and can use healthchecks to remove an item from the list

## DNS Exam Tips

* Routing options
  * Simple - 1 record many IP picked at random, no healthcheck possible
  * weighted - many records with a weight of preference to use
  * latency - checks latency to the requestor and gives the fastest answer
  * failover - uses healthcheck to have primary and secondary
  * geo - uses request location to send request to localized resource
  * multi value - like simple but multiple records and can have health checking to remove failed records from consideration

## Networking Quiz
1. Which AWS service is used to establish a dedicated network connection between your own data center and AWS?
- [ ] Bastion host
- [ ] VPN Gateway
- [ ] Route53
- [ ] Direct Connect
2. Which of the following native AWS services does not support a VPC Endpoint connection?
- [ ] API Gateway
- [ ] DynamoDB
- [ ] Amazon MQ
- [ ] Kinesis Data Streams
3. What type of Route53 record allows you to map a zone apex DNS name to another Route53 record?
- [ ] Alias
- [ ] MX Record
- [ ] CNAME
- [ ] PTR Record
4. Instance 'A' and instance 'B' are running in two different subnets 'A' and 'B' of a VPC. Instance 'A' is not able to ping instance 'B'. Which of the following is a possible reason for this failure?
- [ ] The security group attached to instance 'B' does not allow inbound ICMP traffic; the policy linked to the IAM role on instance 'A' is not configured correctly.
- [ ] The policy linked to the IAM role on instance 'A' is not configured correctly; and the NACL on subnet 'B' does not allow outbound ICMP traffic.
- [ ] The routing table of subnet 'A' has no target route to subnet 'B'; and the security group attached to instance B does not allow inbound ICMP traffic.
- [ ] The NACL on subnet B does not allow outbound ICMP traffic; and the security group attached to instance B does not allow inbound ICMP traffic.
5. You need to ensure that data traveling between AWS infrastructure components is kept within the Amazon network when possible. You have been specifically asked to ensure that data flowing to DynamoDB, S3 and Kinesis Data Streams stays within the VPC. Choose an option below which meets this goal.
- [ ] Add a static route within each routing table to ensure that data for DynamoDB, S3 and Kinesis Data Streams goes directly to a NAT Gateway
- [ ] Only traffic flowing between EC2 instances can be kept within a VPC, traffic to all services must pass directly out to the Internet
- [ ] Create a VPN to allow all data for DynamoDB, S3 and Kinesis Data Streams to pass across it
- [ ] Create a VPC Interface Endpoint for all Kinesis Data Streams and create VPC Gateway Endpoints for S3 and DynamoDB
6. You have configured an EC2 instance, attached an internet gateway, added a route to the internet and configured a new Security Group to allow internet traffic, however you are still unable to access the internet from your EC2 instance. What could be the problem?
- [ ] You haven't configured an Elastic IP address
- [ ] You need to configure a Virtual Private Gateway
- [ ] You need to configure a NAT Gateway
- [ ] You haven't configured a Route53 DNS record
7. Your company processes streaming data from IoT devices. You have a single AWS account containing a VPC, a branch office where many DevOps engineers are located and a presence in a Tier 3 Data centre which houses a Database cluster. Data is streamed into the VPC where it is processed and then sent on to the Database. The AWS Engineers regularly connect into the VPC to perform maintenance. From the options below, choose the most secure, reliable and cost effective solution to connect the VPC to the Data center and the branch office into the VPC.
- [ ] Purchase a 1 gigabit Direct Connect connection to communicate from the branch office to the VPC and a 10 gigabit Direct Connect connection to communicate from the VPC to the Data center
- [ ] Create an EC2 instance in the VPC which is running SSL VPN software, generate certificates for each of the AWS Engineers so that they can connect into the VPC using this software and create an IPSec VPN connection between the VPC and the Data centre for the streamed data
- [ ] Create an IPSec VPN between the branch office and the VPC and purchase a Direct Connect connection to communicate between the VPC and the Data center
- [ ] Create two IPSec VPN connections, one from the branch office to the VPC and one from the VPC to the Data center
8. Your web application has a global user base and you would like to route incoming traffic to the website according to the location of the user in order to give your users a personalized experience depending on their location. Which approach do you recommend?
- [ ] Use Route53 with a Weighted Round Robin routing policy
- [ ] Use Route53 with a Simple Routing policy
- [ ] Use Route53 with a Latency Based routing policy
- [ ] Use Route53 with a Geolocation routing policy
9. You have a number of EC2 instances which need to make wget calls to the internet. Which of the following will need to be in place to enable internet access? (Choose 3)
- [ ] A security group allowing HTTP traffic
- [ ] An Internet Gateway, with an associated route in your route table
- [ ] A Bastion host, with an associated route in your route table
- [ ] A Public IP or Elastic IP address
10. You are having issues sending traffic from your VPC to your Direct Connect connection. You believe it's a routing issue, but you need to confirm this by looking at the relevant logs. Which options will give you the best chance of troubleshooting your problem?
- [ ] Enable and Configure Amazon Inspector
- [ ] Check the CloudTrail logs for your account
- [ ] Utilize the native CloudWatch VPC Network Monitoring logs
- [ ] Enable VPC Flow Logs for your account
11. You have an Amazon VPC with one private subnet, one public subnet, and one network address translation (NAT) server. You are creating a group of EC2 instances that configure themselves to deploy an application via GIT. Which of the following setups provides the highest level of security?
- [ ] Amazon EC2 instances in public subnet; no EIPs; route outgoing traffic via the internet gateway (IGW)
- [ ] Amazon EC2 instances in a private subnet; assign EIPs; route outgoing traffic via the internet gateway (IGW)
- [ ] Amazon EC2 instances in private subnet; no EIPs; route outgoing traffic via the NAT.
- [ ] Amazon ec2 instances in public subnet; assign EIPs; route outgoing traffic via the NAT.
12. You are supporting a highly available web application distributed across multiple AWS Regions and Availability Zones. Your application has a global user base and you need to ensure that users experience the best possible performance. Which routing protocol do you recommend?
- [ ] Weighted Round Robin
- [ ] Latency Based Routing
- [ ] Geolocation
- [ ] Simple Routing Policy
13. What networking components will allow IPv6 data to communicate between a VPC and the internet? (Choose 2)
- [ ] Egress-Only Internet Gateway
- [ ] Internet Gateway
- [ ] Direct Connect
- [ ] NAT
14. Which protocol does AWS Direct Connect use to share routing information?
- [ ] SSH
- [ ] BGP
- [ ] IPSec
- [ ] HTTPS
15. Which subnet mask will give you the largest IP address range?
- [ ] /24
- [ ] /16
- [ ] /28
- [ ] /25
16. You are configuring a new subnet with a /24 subnet mask. How many useable IP addresses will be available for you to allocate?
- [ ] 224
- [ ] 254
- [ ] 256
- [ ] 251
17. How many IP addresses does AWS reserve in every subnet?
- [ ] 3
- [ ] 5
- [ ] 6
- [ ] 4
18. You have created an internet gateway and now need to configure a route to the internet. Which of the following is the correct approach?
- [ ] Create a route with a destination of 0.0.0.0/0 and the target of your Internet gateway ID (igw-xxxxxxxx)
- [ ] Create a route with a target of 169.254.169.254/0 and the destination of your Internet gateway ID (igw-xxxxxxxx)
- [ ] Create a route with a destination of 169.254.169.254/0 and the target of your Internet gateway ID (igw-xxxxxxxx)
- [ ] Create a route with a target of 0.0.0.0/0 and the destination of your Internet gateway ID (igw-xxxxxxxx)
19. You have a number of EC2 instances in a private subnet, how can you securely allow these instances to access the internet?
- [ ] Configure a security group enabling egress traffic for HTTP on port 80 and 443
- [ ] Attach an Internet Gateway to your VPC and create a route out to the internet through the Internet Gateway
- [ ] Configure a Bastion host and a route out to the internet via the Bastion
- [ ] Create a NAT gateway and configure a route to the internet via the NAT gateway
20. Which subnet mask will give you the smallest IP address range?
- [ ] /16
- [ ] /24
- [ ] /28
- [ ] /25
21. Which of the following DNS record types does Route 53 not support?
- [ ] DNSKEY
- [ ] SPF
- [ ] AAAA
- [ ] CNAME
22. Your website is evenly distributed across 10 EC2 instances in 5 AWS regions. How could you configure your site to maintain high-availability with minimum downtime if one of the 5 regions was to lose network connectivity for an extended period of time?
- [ ] Create a Route 53 Latency-based Routing Record Set that resolves to an Elastic Load Balancer in each region. Set an appropriate health check on each ELB.
- [ ] Establish VPN Connections between the instances in each region. Rely on BGP to failover in the case of a region-wide connectivity outage.
- [ ] Create a Route 53 Latency-based Routing Record Set that resolves to Elastic Load Balancers in each region and has the Evaluate Target Health flag set to "True".
- [ ] Create an Elastic Load Balancer to place in front of each EC2 instance. Set an appropriate health check on each ELB.
### Key
1. Direct Connect
2. Amazon MQ
3. Alias
4. The NACL on subnet B does not allow outbound ICMP traffic; and the security group attached to instance B does not allow inbound ICMP traffic.
5. Create a VPC Interface Endpoint for all Kinesis Data Streams and create VPC Gateway Endpoints for S3 and DynamoDB
6. You haven't configured an Elastic IP address
7. Create an IPSec VPN between the branch office and the VPC and purchase a Direct Connect connection to communicate between the VPC and the Data center
8. Use Route53 with a Geolocation routing policy
9. all but `A Bastion host, with an associated route in your route table`
10. Enable VPC Flow Logs for your account
11. Amazon EC2 instances in private subnet; no EIPs; route outgoing traffic via the NAT.
12. Latency Based Routing
13. `Internet Gateway`, `Egress-Only Internet Gateway`
14. BGP
15. /16
16. 251
17. 5
18. Create a route with a destination of 0.0.0.0/0 and the target of your Internet gateway ID (igw-xxxxxxxx)
19. Create a NAT gateway and configure a route to the internet via the NAT gateway
20. /28
21. DNSKEY
22. Create a Route 53 Latency-based Routing Record Set that resolves to Elastic Load Balancers in each region and has the Evaluate Target Health flag set to "True".