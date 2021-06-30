# Security and Compliance
- [Security and Compliance](#security-and-compliance)
  - [Compliance On AWS](#compliance-on-aws)
  - [DDoS](#ddos)
    - [Tips](#tips)
  - [AWS Marketplace Security Products](#aws-marketplace-security-products)
    - [Tips](#tips-1)
  - [IAM Custom Policies Lab](#iam-custom-policies-lab)
  - [Roles & Custom Policies Lab](#roles--custom-policies-lab)
    - [Tips](#tips-2)
  - [MFA & Reporting With IAM Lab](#mfa--reporting-with-iam-lab)
    - [Tips](#tips-3)
  - [Security Token Service](#security-token-service)
    - [Tips](#tips-4)
  - [Security & Logging](#security--logging)
    - [Tips](#tips-5)
  - [AWS WAF](#aws-waf)
    - [Tips](#tips-6)
  - [AWS Hypervisors](#aws-hypervisors)
    - [Tips](#tips-7)
  - [Dedicated Instances Vs Dedicated Hosts](#dedicated-instances-vs-dedicated-hosts)
    - [Tips](#tips-8)
  - [AWS Systems Manager EC2 Run Command](#aws-systems-manager-ec2-run-command)
    - [Tips](#tips-9)
  - [AWS Systems Manager Parameter Store](#aws-systems-manager-parameter-store)
    - [Tips](#tips-10)
  - [Pre-signed URLs with S3](#pre-signed-urls-with-s3)
    - [Tips](#tips-11)
  - [S3 - Restrict IP Addresses](#s3---restrict-ip-addresses)
  - [AWS Config With S3](#aws-config-with-s3)
  - [Inspector (security) vs Trusted Advisor (general)](#inspector-security-vs-trusted-advisor-general)
    - [Tips](#tips-12)
  - [AWS Service Limits](#aws-service-limits)
    - [Tips](#tips-13)
  - [Shared Responsibility Model](#shared-responsibility-model)
    - [Tips](#tips-14)
  - [Other Security Aspects](#other-security-aspects)
  - [CloudTrail - Turning It On and Validating Logs](#cloudtrail---turning-it-on-and-validating-logs)
  - [CloudTrail - Protecting Your Logs](#cloudtrail---protecting-your-logs)
    - [Tips](#tips-15)
  - [Security Summary](#security-summary)
  - [Security & Compliance Quiz](#security--compliance-quiz)
    - [Key](#key)
  
## Compliance On AWS

* 3 Frameworks
  * PIC Security Standards council
  * ISO
  * HIPAA - health care info
* ISO 27001 
  * Get through auditing based on having security management system for how you manage security management system within the context of the overall business risks
* FedRAMP
  * Federal Risk and Authorization management program
  * A US wide program for a standardized approach to security assessment, etc.
* HIPAA
  * Health insurance portability and accountability act
  * Intended to make it easier for people to keep health insurance, product privacy, provide security of health information and control costs
  * Not all services are by default but most are and are always moving to be compliant
* NIST - Improving critical infrastructure cybersecurity
* PCI - Payments card industry data security standard; AKA credit cards, debit cards, etc using 12 rules:
  * Install and maintain a firewall config to protect cardholder data
  * Do not use vendor-supplied defaults for passwords or other security parameters
  * Protect stored cardholder data
  * Encrypt transmission of cardholder data across open networks
  * Protect all systems against malware and regularly update anti-virus software
  * Develop and maintain secure systems and applications
  * Restrict access to cardholder data by business need to know
  * Id and authenticate access to system components
  * Restrict physical access to cardholder data
  * Track and monitor all access to network resources and cardholder data
  * Regularly test security systems and processes
  * Maintain a policy that addresses information security for all personnel
* SAS79
  * Auditing Standards
* SOC1
  * Accounting standards
* FIPS
  * US gvt standard to approve crypto modules

## DDoS

* DDoS whitepaper 
* Denial of service attack attempting to make your website or application unavailable to your end users via multiple methods
* Amplification/reflection attack
  * Includes things like NTP,SSDP,DNS,Chargen,SNPM, etc where an attacker may send a 3rd party server a request using a spoofed IP. That server will then respond to that request with a greater payload than the initial request (28 -54 x larger than the request) to the spoofed address
  * That allows the attacker using the spoofed IP to send out 64 byte requests with the 3rd party sending back up to 3k bytes back. Attackers can co-ordinate this and use multiple NTP servers a second to send traffic to the target
* Layer 7 attack
  * Flood with GET requests
  * Slowloris - Send requests keeping and holding connections as long as possible.
* Mitigating DDoS
  * Minimize the attack surface area
  * Be ready to scale to absorb the attack - ASG for example
  * Safeguard exposed resources
  * Learn normal behavior
  * Create a plan for attacks
* AWS Shield
  * Free service that protects all customers on EBS, CloudFront, and Route 53
  * Protects against SYN/UDP floods, reflection attacks and other layer 3/4 attacks
  * Advanced provides enhanced protection against more sophisticated attacks at $3,000/month providing a dedicated team and protests against the costs involved with responding
    * Advanced shield provides always-on flow-based monitoring of network traffic and active application monitoring to give near real-time notifications of DDoS attacks
    * Gives a 24x7 response team at AWS to manage and mitigate application layer attacks
    * Protects the bill against higher fees caused by the attack

### Tips
* Read the whitepaper
* Remember what can be used to mitigate the attack
  * Cloudfront
  * R53
  * ELB
  * ASG
  * Web application firewall (WAFs)
  * Cloudwatch

## AWS Marketplace Security Products

* Marketplace lets you provision pre-configured AMIs or training, hardened AMIs etc.
* They have lots of catagories including SaaS
* Go under Security and check under your region
* Kali Linux is a pure standard in the industry
* AWS provides pen testing, there is a form you have to fill out before starting.  **YOU MUST DO THAT APPROVAL** Even when using a marketplace product you must still fill out the form

### Tips

* You can get many security productions via the marketplace

## IAM Custom Policies Lab

* Start from IAM and select policies
* Create a policy
  * Service = S3
  * Actions = Alllist, allread
  * Resources = all
  * Name = MyCustomROS3policy
* Create a role on EC2
  * Add MyCustomROS3policy
  * Name the role

## Roles & Custom Policies Lab

* Start an EC2 instance
* Include the role from above
* Confirm that you can read from buckets but not write from the shell of the instance
* Changes to IAM can take a few minutes at times
* Update the policy (because that sets what the role can do) and add write permissions
* Again, not instant to change, but should be quick
  
### Tips

* Create policies using editor or json
* Attach policies at any time with CLI or console
* Once attached it takes affect right away, same for changes to the policy

## MFA & Reporting With IAM Lab

* MFA and reporting in IAM
* IAM dashboard tells you right away if MFA isn't enabled on root
* When enabling it gives a QR code and you can keep a copy of that QR code to update your app if you need to
* For a user you can add MFA in a few ways
  * Console you can just edit the user under security code and add as normal
  * CLI is different and needs key and secret that has the permissions to do IAM MFA
  * `aws iam create-virtual-mfa-device --virtual-mfa-device-name EC2-User --outfile /home/ec2-user/QRCode.png --bootstrap-method QRCodePNG`
  * Use the QR code with your MFA app
  * `aws iam enable-mfa-device --user-name EC2-User --serial-number arn:aws:iam::"USERNUMBERHERE":mfa/EC2-User --authentication-code-1 "CODE1HERE" --authentication-code-2 "CODE2HERE"`
  * You can use awsCLI with MFA as well using sts 
* Credentials report shows all users and if they use MFA

### Tips

* Enable with CLI or console
* For root and / or users
* Can be forced to be used with CLI 
* Reports can be made from in IAM on users

## Security Token Service

* Grants users limited and temp access to resources
  * AD users
    * Uses SAML
    * Grants temp access based off of AD credentials
    * Doesn't need to be an IAM user
    * SSO allows AWS console without assigning IAM credentials
  * Mobile Apps
    * Facebook/Google or other OpenID providers
  * Cross Account
    * Users from one account access resources in another
* Example
  * Your internal site lives in the VPC. Users login that authenticates against AD living at headquarters. Your VPC is connected vi IPSEC VPN. Once users are logged in they get access to their own S3 bucket. How to setup?
    * WEB App uses identity broker to authenticate against AD 
    * Then gets STS token that goes back to the app
    * That token goes against s3 where the token gets validated to allow access

### Tips

* Remember the above flow, AD auth -> STS -> web app -> AWS service <-> Verify token with IAM

## Security & Logging

* Security at scale white-paper is interesting
* Developed under
  * ISO 27001
  * PCI DSS v2
  * FedRAMP
* Always lock down log access :
  * IAM
  * S3 Policies
  * MFA
* Ensure organizational based role based access:
  * IAM
  * S3 Policies
* Alerts when logs are created or fail
  * Cloudtrail notifications
  * Config rules
* Alerts should be specif but not divulge details
  * Location of a log, not the contents
* Log changes to system components
  * AWS config
  * CloudTrail
* Controls exist to prevent modifications to logs
  * IAM + S3 
  * CloudTrail log validation 
  * CloudTrail log encryption

### Tips

* Services
  * CloudTrail
  * Config
  * CloudWatch Logs
  * Flow Logs
* CloudWatch is performance
* CloudTrail is audit
* Config records and reports on the state of the environment
  
## AWS WAF

* Web application firewall that lets you monitor the HTTP(S) requests forwarded to CloudFront, ALB or API gateway. 
* Like a firewall it can let you control access to the resource
* You can configure conditions like what IP addresses are allowed to make requests or what parameters need to be passed for the request to be allowed. Failing to include required parameters returns a 403 status code
* At most basic it allows
  * Allow all but specific requests
  * Block all but specific requests
  * Count requests that match specific requests
* Specific requests can be things like:
  * IP of requestor
  * Country of requestor
  * Values in request headers
  * Strings that appear in the requests, including regex
  * Length of request
  * Inclusion of SQL code
  * Inclusion of script likely to be malicious
* Integrates with
  * ALB
  * Cloudfront
  * API Gateway
* Doesn't support
  * Classic or Network load balancers
  
### Tips

* Web application firewall that lets you monitor the HTTP(S) requests forwarded to CloudFront, ALB or API gateway. 
* Controls access to content

## AWS Hypervisors

* A hypervisor or VMM is a service that creates and runs virtual machines. A computer on which a hypervisor runs one or more VM's is a host machine and each VM is a guest machine.
* EC2 is on the Xen hypervisor with guests running either Paravirtualization (PV) or Hardware virtual machine (HVM)
* HVM guests are fully virtualized, with the VM's on top of the hypervisor not aware they are sharing processing time with other VMs
* PV is lighter virtualization and it use to be quicker
* In PV
  * Ring 0 is the host
  * Ring 1 is the VM
* Isolation (lowest to highest)
  * Physical interface
  * Firewall
  * Security groups
  * Virtual interface
  * hypervisor
  * customer guests
* Admins with a business need to access the management plane are required to use MFA to gain access to purpose-built hosts. These admin hosts are systems that are specifically hardened to protect the management plane. All access is logged and audited. When there is no longer a business need to access the mgt plane the privileges and access can be revoked
* Guest access is controlled by the customer via key pairs, ssh, rdb, etc.
* EBS automatically resets every block of storage used so there is never exposure to other customers
* Memory is also scrubbed before re-use on a new guest
  
### Tips

* HVM over PV when possible
* PV is isolated by layers
* Only AWS admins have access to hypervisors
* AWS staff do not have access to EC2, that is the customers responsibility
* All storage is scrubbed before being delivered

## Dedicated Instances Vs Dedicated Hosts

* Dedicated instance are run in a VPC on hardware that is dedicated to a single customer. Instances are isolated at the host hardware level from other accounts
* Dedicated instances may share hardware with other instances from the same account that are not dedicated instances
  * Can be on-demand, reserved or spot as normal
* EC2 dedicated hosts
  * Sets the physical host to you and gives some additional visibility on how the hosts are deployed. Mostly related to licensing requirements.

### Tips

* Both dedicated instances and dedicates hosts have dedicated hardware
* Dedicated instances are charged by the instance, dedicated hosts are charged by the host
* Meets specific regulatory or licensing conditions via dedicated hosts
* Dedicated instances may share the host with other guests from the same account that are themselves not dedicated
* Dedicated hosts give better visibility into things like sockets, cores, and host ID.

## AWS Systems Manager EC2 Run Command

* Allows automation of common admin tasks or ad-hoc configuration changes to an entire fleet without needing to connect to each instance
* Requires a role attached to managed instances.
  * That role needs be against ec2 and there is a sample role provided to you.
  * SSM is often based off of tags but can use instance ID
  * The service **DOESN'T** need the specific port open as for manual connect (SSH / RDB)
  * With requirement done you can now `run command` by selecting the target
  * Add options and parameters as needed. It also includes the CLI version for re-use
  * On complete you can see the outputs

### Tips

* Commands can be applied to a group of instances based on tags or manual selection
* SSM agents needs to be installed on all managed instances
* Commands and parameters are defined in a JSON document
* Commands can be issued using Console, CLI, APIs, SDKs, etc
* You can use this service with on-prem hardware

## AWS Systems Manager Parameter Store

* Passing secrets via parameter store
* Key - Pair values + metadata
  * Name
  * Description 
  * Type (string, list, KMS encrypted)
  * Value
* Can be read by lambda, cloudformation, systems manager
* Can be read via aws CLI, `aws ssm get-parameters --names "helloWorld"`

### Tips

* A way to keep any confidential information in SSM Parameter store
* Access from a number of services via API calls or via the aws CLI

## Pre-signed URLs with S3

* Access bucket / objects from private locations on demand.
* Either via SDK or even CLI
* Needs a role that allows admin access to S3
* `aws s3 presign s3://$BUCKET/$OBJECT`
  * Default of 60 minutes of access
* Returns the pre-signed url to access the target

### Tips

* Access private objects without needing more complicated policies via pre-signed URLs
* Normally done via the SDK but 100% works from the cli as well
* Expires after set time, either 1 hr or `--expires-in` number of seconds

## S3 - Restrict IP Addresses

* You can restrict access to your S3 addresses so that only particular IP ranges have access. You may do this to the external or internal ranges.
```json
{ 
    "Version": "2012-10-17",
    "Id": "S3PolicyID1",
    "Statement": [
        {
            "Sid": "IPAllow",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:*",
            "Resource": "aws:aws:s3:::$BUCKET/*",
            "Conndition": {
                "IpAddress": {"aws:SourceIp:10.0.1.0/24"},
                "NotIpAddress":{"aws:SourceIp:54.240.143.188/32"}
            }
        }
    ]
}
```

## AWS Config With S3

* In config console filter to s3
* Enable public R/W prohibited

## Inspector (security) vs Trusted Advisor (general)

* Inspector is an automated security assessment service to help improve applications deployed on AWS.
* It automatically assess applications for vulnerabilities or deviations from best practices
* Produces detailed list of security findings ordered by severity
  * Works from an assessment target by tags
  * Requires agent on EC2, maybe via systems manager
  * The template has a template name and rules packages (best practices, runtime behavior, etc)
  * Once created you have to run it, at least an hr for data gathering.
* Master templates to test all rules 
* Trusted advisor covers cost, access, etc.
  * Many are turned off for non-business type accounts
  * Gives notice about best practices, service limits, etc
  * No agent

### Tips

* Inspector
  * Creates assessment target 
  * Install an agent
  * Create a template and run it
  * Review findings against the rules provided by AWS
  * Reports severity levels
  * Monitors the target and reports on issues seen during the review and advise based on findings
  * Doesn't fix things, still the customers responsibility to deal with alerts
* Trusted advisor
  * Cost optimization
  * availability
  * performance
  * general security

## AWS Service Limits

* Every account has default service limit of how many resources can be provisioned per-account. 
* Prevents accidental over deployment or if your account is compromised 
* Trusted advisor offers information about service limits

### Tips

* All services have per-region limits that can be seen in trusted advisor

## Shared Responsibility Model

* AWS manages security **OF** the cloud (getting into the services), the customer manages security **IN** the cloud (SSH keys, securing S3 buckets, secure applications, along with keeping the AWS credentials secure)
* AWS does
  * Global infrastructure
  * Hardware, software, networking, and facilities
  * 'managed services'
* Customer does
  * IaaS (ec2)
  * Patching
  * AWS firewall / security groups
  * IAM
* Some changes depending on the service type
  * Infrastructure 
    * Compute, EBS, Autoscaling, VPC. Customer manages these things as if it was your data center
  * container
    * A service running where you don't manage the OS, like RDS or beanstalk, Customer owns data / application
  * abstracted
    * High level storage, DB's or messaging services, All AWS outside of controls you have like access policies

### Tips

* Understand who owns what
* You own OS patching, security groups, VPC, network ACL's etc
* You don't own the OS on services where you have no shell access like RDS or Elasticbeanstalk

## Other Security Aspects

* Security groups are stateful
  * If you open a port on inbound it also address outbound (adding inbound 22 includes outbound)
  * Read security group rules
  * Public / private subnets
    * Internet gateway -> router -> route table -> network acl -> security group
      * CloudTrail logs API calls to S3
      * Could query logs with Athena to find who is making things
  * AWS Artifact
    * On-demand downloads of security and compliance documents. You can submit documents to auditors or regulators to validate the security and compliance of services you use
  * HSM vs KMS
    * HSM is single tenant
    * HSM gives you control of the keys
    * Both are FIPS compliant, but KMS is level 2, HSM is level 4, but for an extra cost
  * Instant encryption -> s3
  * Encryption via migration -> DynamoDB, RDS, EFS, EBS

## CloudTrail - Turning It On and Validating Logs

* Records API calls and logs them to S3
* Allows after the fact investigation
* Near real time intrusion detections
* Industry compliance
* What is logged
  * metadata around the call
  * who made the call
  * time / source of the call
  * Request parameters
  * result response
* All logs sent to a bucket with whatever retention you set and delivered every 5 minutes with up to a 15 minute delay
* Can use SNS notifications
* Can be aggregated across regions or accounts
* Setup?
  * Enabled by default for 7 days worth
  * If you want it for longer you have to provision it
* Under MGT tools you can see your recent events
* Create a new CloudTrail and select which regions to apply it to.
* Select the event types (read / write)
* Data events 
* Create the trail
* The S3 will also create a digest if you enable validation
  * The digest is made each hr and provides a hash of each file 

## CloudTrail - Protecting Your Logs

* Logs contain metadata not application data, but can have PII of usernames, DB table names, group names, etc.
* Start with IAM policies and S3 bucket policies to restrict access to the bucket holding the logs
* You can also encrypt the bucket
* To restrict to the correct class of staff use IAM groups to allow read access
  * Can have full or read only access
* Notification of logs
  * Configure SNS and log validation and develop a solution that when triggered by SNS to validate the logs using the digest file. With notification when it doesn't match
* Prevent log files from deletion
  * IAM and bucket policies or S3 MFA delete
* Log retention
  * Default is forever
  * S3 lifecycle management is more common to either expire old logs or move them to cheaper storage

### Tips

* Logs any API call with enough data to know who, what, when, how. Doesn't log connection actions like ssh
* Delivered every 5 minutes as needed with up to 15 minute event delay
* SNS 
* Can aggregate across regions or accounts
* Validation via digest files every hr to validate via has key
* Protect the logs since they can have PII or for audit reasons, only give as much access as required
  * IAM, MFA delete, Lifecycle rules and S3 policies

## Security Summary

* Compliance frameworks out of the box like HIPAA, ISO, PCI-DSS among others. This only covers the platform not your application
* DDoS
  * Good White paper
  * Mitigated with Shield in:
    * Cloudfront
    * Route 53
    * ELB
    * WAFs
    * Autoscaling
    * Cloudwatch
  * Shield is on by default but the advanced is several thousand / month
    * The advanced version does cover costs related to scale up dealing with DDoS and gives 24x7 dedicated response teams
* Marketplace lets you get products from 3rd parties like firewalls, pre-hardened OS, Firewalls, antivirus or even training.
  * Price could be free or time based
* Iam
  * Can create custom policies
  * Can attach roles to instances at any time
  * Change is right away
  * MFA via command line or console
  * Any user, root or other
  * MFA on CLI is possible
  * Reporting from IAM is possible to show who is or isn't using it among other things
* SSO via AD authentication to STS to get a token that can be used with other API's to validate use, no IAM is required
* Logging Services
  * CloudTrail - Auditing 
  * Config - State / compliance
  * CloudWatch - Performance / health
  * Flow logs
* WAFs
  * Web application firewall, level 7 aware (HTTP/S) to control content to CloudFront or ALB
* Hypervisors
  * Use HVM when possible
  * AWS admins get access to the hypervisor as needed
  * All storage is scrubbed before delivery
  * Not classic or network balancers
* Dedicated instance vs dedicated host
  * Both get dedicated hardware
  * dedicated instances could have other instances on the host from the same account and you are charged by the instance
  * Dedicated hosts are charged by the host and would meet requirements for regulations or licensing.
  * Dedicated hosts gives extra visibility of things like sockets, cores, host ID
* System manager - run command
  * Applies commands to groups of systems by tag or manual selection
  * Requires an agent be installed
  * Commands and parameters are in a 'document'
  * Commands can be issued using Consolle, CLI, SDK etc
  * You can manage on-prem with this tool as well
* Parameter store
  * Manage secrets as SSM parameter store, including encryption
  * Can use in a number of services
* Pre-signed URLs
  * Normally SDK
  * Access normally private items with pre-signed url for some time, normally 1 hr
* Config can manage S3 best pratices (public read/write)
* Inspector
  * Create security audit document
  * Doesn't fix things, is only an audit
  * Required agent, so ec2 only
  * Create a template against a target and run it
  * AWS provides a number of standard rule sets to check against
  * Reports in normal severity levels 
* Trusted Advisor
  * More cost / performance focused
  * No agent
  * Many items are walled off to paid accounts
  * Some security
* Shared responsibility
  * OS you control
  * Settings you control (firewalls, SG)
  * Not for items you don't have control over or are provided like RDS or elasticbeanstalk
* Service limits
  * By region and shown in trusted advisor
* Security groups are stateful, give ingress and you get egress on the same port
* Reading security groups, now that security groups can include security groups
* CloudTrail can tell you who makes items. Large orgs should use AAthena to read the data
* Artifact
  * Document service to validate AWS is complaint against a given standard. It doesn't do anything
* HSM vs KSM
  * HSM does semetric and asym, KSM is only asym
  * Both are FIPS, but HSM is a higher level with more cost
* Encryption
  * S3 is any time any place
  * Other stores require migration
    * DynamoDB
    * RDS
    * EFS
    * EBS
* CloudTrail events
  * To S3 every 5 minutes with up to 15 minute event delay
  * Aggregated cross region / accounts
  * Validation with digests of hash values
  * SNS of course
  * S3 lifecycle will keep from massive storage use

## Security & Compliance Quiz

1. You are creating a fleet of EC2 instances that will be inside an autoscaling group. These EC2 instances will need to write a custom metric to Cloud Watch and will need the appropriate permissions with which to do this. What is the most secure way to enable this?
- [ ] Create a unique user in IAM with CloudWatch permissions and modify the autoscaling group to include a boot strap script that passes the EC2 instance that users credentials.
- [ ] Create an IAM role with CloudWatch permissions and modify the autoscaling launch configuration to use EC2 instances that have been assigned the new role.
- [ ] Create an IAM role with CloudWatch permissions and assign this to RDS. The existing EC2 instances will automatically be able to report to CloudWatch via RDS.
- [ ] Create a unique user in IAM with CloudWatch permissions and store these credentials in GitHub. Have the EC2 instances pull these credentials when they need to log to CloudWatch
2. AWS Systems Manager Parameter Store provides secure, hierarchical storage for configuration data and secrets management. Which of the following AWS services natively support the Parameter Store? (Choose 3)
- [ ] Amazon EC2
- [ ] AWS CloudFormation
- [ ] AWS Lambda
- [ ] Amazon RDS
3. Given the following IAM policy: 
```json
{ "Version": "2012-10-17", "Statement": [ { "Effect": "Allow", "Action": [ "s3:Get*", "s3:List*" ], "Resource": "*" }, { "Effect": "Allow", "Action": "s3:PutObject", "Resource": "arn:aws:s3:::corporate_bucket/*" } ] }
```
, what does the IAM policy allow? (Choose 3)
- [ ] The user is allowed to read objects from the bucket named "corporate_bucket".
- [ ] The user is allowed to write objects into the bucket named "corporate_bucket".
- [ ] The user is allowed to read objects from all S3 buckets owned by the account.
- [ ] The user is allowed to change access rights for the bucket named "corporate_bucket".
- [ ] The user is not allowed to list the objects in the bucket named "corporate_bucket".
4. Per the AWS Acceptable Use Policy, penetration testing of EC2 instances ________.
- [ ] May be performed by the customer against their own instances, only if performed from EC2 instances.
- [ ] May be performed by AWS, and will be performed by AWS upon customer request.
- [ ] May be performed by AWS, and is periodically performed by AWS.
- [ ] May be performed by the customer against their own instances without prior authorization from AWS.
5. You are supporting a large environment running in AWS. The Security architect in your organization asks you to implement a configuration management tool to record the state of your infrastructure and notify you of any changes to the baseline. Which service can you use to achieve this?
- [ ] CloudTrail
- [ ] Systems Manager
- [ ] AWS Config
- [ ] CloudWatch
6. STS (Security Token Service) grants temporary access to AWS resources to users authenticated using which methods? (Select THREE) (Choose 3)
- [ ] Cross Account Access
- [ ] AWS Rekognition
- [ ] Active Directory Federation
- [ ] Federation with Web Identity Providers
- [ ] Cross-Origin Resource Sharing
7. Your organization is being audited and you are asked to implement monitoring for every single API call which occurs in your AWS account. Which service can you use to achieve this?
- [ ] AWS Config
- [ ] AWS Inspect
- [ ] CloudTrail
- [ ] CloudWatch
8. Your company has asked you to investigate the use of KMS for storing and managing keys in AWS. From the options listed below, what key management features are available in KMS?
- [ ] Generate keys, disable and delete keys, operate as a private, native Hardware Security Module (HSM)
- [ ] Import your own keys, disable and re-enable keys and migrate keys between the default KMS key store and a custom key store
- [ ] Import your own keys, disable and re-enable keys and define key management roles in IAM
- [ ] Generate keys, disable and re-enable keys and import keys into a custom key store
9. In an IAM policy, what action does IAM:PassRole relate to? (Choose 2)
- [ ] Passing a role to an IAM user
- [ ] Passing a role to an AWS service to assign temporary permissions to the service
- [ ] Passing a role to another AWS account
- [ ] Associating a role with an EC2 instance
10. You are working on a project to migrate a banking application to AWS. Your Security Architect asks if there is a single place where you can securely store user passwords, database connection strings and license codes. What do you suggest?
- [ ] Systems Manager Parameter Store
- [ ] RDS
- [ ] DynamoDB
- [ ] S3
11. The security team have asked you to provide them with details of all the IAM users in your account and the status of their credentials including passwords, access keys and registered MFA devices. What is the best way to approach this?
- [ ] Create a custom script to generate the report
- [ ] Generate a credential report either using the AWS CLI or from the AWS console
- [ ] Generate an IAM user report from the IAM dashboard in the AWS console
- [ ] Generate an IAM status report from the IAM dashboard in the AWS console
12. Which feature can be used to configure console access for users authenticated by Active Directory?
- [ ] IAM
- [ ] Federated authentication with STS
- [ ] Web Identity Federation
- [ ] Cognito
13. Which of the following statements are correct regarding Multi-Factor Authentication (MFA)? (Select TWO) (Choose 2)
- [ ] You can enable MFA using the console only
- [ ] You can enforce the use of MFA using IAM
- [ ] You can enable MFA using the command line or the console
- [ ] You can enforce the use of MFA using the STS (Security Token Service)
14. Which of the following is an Identity Broker that can be used to enable Active Directory accounts to access AWS resources?
- [ ] Web Identity Federation Services
- [ ] IAM
- [ ] Active Directory Federation Services
- [ ] CORS
15. Which AWS service can you use to protect against DDoS attacks?
- [ ] AWS Systems Manager
- [ ] Trusted Advisor
- [ ] AWS Shield
- [ ] Security Groups and Network ACLs
16. Which of the following AWS services allow native encryption of data, while at rest? (Choose 3)
- [ ] Elastic File System (EFS)
- [ ] S3
- [ ] Elastic Block Store (EBS)
- [ ] Elasticache for Memcached
17. Which service can you use to run a command on group of systems based on tags?
- [ ] Systems Manager Run Command
- [ ] CodeCommit
- [ ] AWS Config
- [ ] AWS CLI
18. What does the following policy do: { "Version": "2012-10-17", "Statement": [ { "Action": [ "autoscaling:Describe*", "cloudwatch:*", "logs:*", "sns:*" ], "Effect": "Allow", "Resource": "*" } ] }
- [ ] Allows full access to RDS
- [ ] Allows full access to CloudWatch
- [ ] Allows Read Only Access to CloudWatch
- [ ] Allows Write & Read Access to Cloudwatch only.
19. You are supporting a web application that runs on 3 EC2 instances. Your users must log in to the application which authenticates against the Active Directory service in your own Data Centre. You want to ensure that once the user logs in, they only have access to the AWS resources they need. Which services can you use to configure this? (Choose 3)
- [ ] Security Token Services
- [ ] IAM
- [ ] CORS
- [ ] Active Directory Federation Services
20. How can you determine which of your IAM Users have configured Multi-Factor Authentication (MFA)?
- [ ] Use Trusted Advisor
- [ ] Generate a user authentication report
- [ ] Generate a report using AWS Shield
- [ ] Generate a credential report
21. You are working on a project to launch an application which stores highly confidential data. Your compliance team advise that they do not want to host the application on multi-tenant hardware. Which class of EC2 instance can you use to host the application?
- [ ] Dedicated Instances
- [ ] Spot Instances
- [ ] Reserved Instances
- [ ] On-Demand Instances

### Key

1. Create an IAM role with CloudWatch permissions and modify the autoscaling launch configuration to use EC2 instances that have been assigned the new role.
2. All but Amazon RDS
3. `The user is allowed to read objects from the bucket named "corporate_bucket"`, `The user is allowed to write objects into the bucket named "corporate_bucket"`, and `The user is allowed to read objects from all S3 buckets owned by the account.`
4. May be performed by the customer against their own instances without prior authorization from AWS.
5. AWS Config
6. Cross Account Access, Active Directory Federation, Federation with Web Identity Providers
7. CloudTrail
8. Import your own keys, disable and re-enable keys and define key management roles in IAM
9. Passing a role to an AWS service to assign temporary permissions to the service, Passing a role to another AWS account
10. Systems Manager Parameter Store
11. Generate a credential report either using the AWS CLI or from the AWS console
12. Federated authentication with STS
13. `You can enforce the use of MFA using IAM`, `You can enable MFA using the command line or the console`
14. Active Directory Federation Services
15. AWS Shield
16. All but `Elasticache for Memcached`
17. Systems Manager Run Command
18. Allows full access to CloudWatch
19. All but CORS
20. Generate a credential report
21. Dedicated Instances