# Production deployments

One of the most common questions that people ask is how do I deploy Kubernetes to production. Until versions 1.4 and 1.5 it was difficult to deploy Kubernetes to a production environment. In the container community it was well known that Kubernetes is a great tool, but at the time it was almost impossible to deploy and manage. Fortunately, to the credit and growth of Kubernetes and its community, a lot of work has been performed in this space and it's much easier to deploy today. So let's take a look at some of the most common ways to install Kubernetes.

If you're a DevOps engineer, tasked with getting Kubernetes into production, I would recommend reading through Kelsey Hightower's Kubernetes the Hard Way. It documents, in detail, all the components that need to be installed to get it running and avoids any scripts. This is really helpful so that when something does break in your production environment you know how to react and what all the components are. The most common way to install K8s today is using the kubeadm tool, or kubeadm as some people call it. This is probably the easiest way to install it on any public cloud, private cloud, or on-premise infrastructure.

Essentially you are required to initially provision the master host with Docker and the Kubernetes distribution you're looking for.

Once this is done, you can run `kubeadm init`, which starts up the kubeadm tool and provisions the control plane. Once completed, kubeadm will provide you with a token called a join token. On each of the worker nodes that you're trying to provision you can simply run kubeadmn join with your join token and the workers will join your cluster. Once the nodes have joined, you'll need to install a pod network for your pods to be able to communicate with each other.

Kubernetes has only three basic rules for this.

* One, all containers can communicate with other containers without a NAT.
* Two, all nodes can communicate with all containers and vis versa without a NAT.
* Three, the IP that a container sees itself is the same IP that others see it as as well.

There are different networking solutions that you can implement which have different pros and cons depending on your infrastructure needs. However Flannel and Weave Net are a great place to start. I've included additional networking resources in the handout provided in the exercise files. So take a look.

If you're working on a AWS infrastructure and you're wanting to install a cluster then kops is the tool for you. Kops has a number of useful features. It automates the Kubernetes cluster provisioned in Amazon Web Services, it deploys highly available masters, also known as HA, it permits upgrading with kube-up, it's uses as a state-sync model for dry runs and automatic idempotency, it generates configuration files for AWS CloudFormation and Terraform configurations, it supports custom add-ons, and finally it uses manifest-based API configurations.

Kops is currently the best way to deploy Kubernetes to an Amazon Web Services environment and it looks very similar to the way that kubectl operates. If you're trying to deploy a Kubernetes instance to another cloud provider like Azure, Google Compute, or Oracle Cloud, you can use one of the native cloud services like Azure Container Service for Azure, Google Container Engine for Google Compute, or Oracle Container Engine for Oracle Cloud.

Amazon Web Services is also expected to announce a new Kubernetes engine at re:Invent in 2017. So you might not even have to configure kops to get started with it. A Kubernetes install isn't as hard as it used to be with the advent of new tools like kubeadm and kops and most cloud providers are already doing a lot of the heavier lifting for you in terms of getting a production-worthy platform up and running.

## Namespaces

Namespaces are a fundamental concept to add multi-tenancy to your Kubernetes instance. Kubernetes provides multiple virtual clusters backed by the same physical cluster. These virtual clusters are called namespaces. There are four primary use cases.

* One, roles and responsibilities in an enterprise.
* Two, partitioning landscapes, for example, dev vs test vs production.
* Three, customer partitioning for non-multi-tenant scenarios. For example, if you're a consulting company and you have multiple customers, you can use this feature.
* And finally, for application partitioning as well.

First, let's talk about the reuse case related to roles and responsibilities in  an enterprise. Enterprises have many teams that typically operate independently of each other and might have some shared interfaces and APIs to communicate with each other. The use of namespaces is perfect in this scenario, because teams are able to operate independently without stepping on each other. Namespaces also prevent them from confusing services and deployments that might not belong to them. Here are a couple of things you'll need to watch out for.

* Plan in advance how you want to manage your enterprise in a Kubernetes environment. Setting standards up front will help you in the long-term with infrastructure management.
* Don't simply transpose existing on-premise controls and procedures to the new environment. This might result in bringing your existing infrastructure baggage to the new environment, which is supposed to be more agile. 

Another common pattern is using namespaces for Dev, Test, and Production environments. With most teams building a continuous integration,
or CI pipelines, you can easily define CI pipelines to deploy an entire environment in a quick and easy fashion. Some anti-patterns to watch out here for are,

* sometimes you will end up with a really large namespace because you have many applications that are running. In these scenarios, it might be good to create additional namespaces for groups of application. For example, E-Commerce Dev namespace for all E-commerce related applications.
* Another scenario is, you might end up with too many environments. Just because you can, does not mean that you should. Don't abuse the feature because it will result in too many unnecessary environments. If you don't use a staging deployment, or you don't use a staging namespace, then don't create one.

Consulting companies and small software vendors might use this method a lot. You could create a namespace for each customer or project to keep them distinct, while not needing to worry about reusing the same names or resources across different projects. A new side effect of using the Helm
package manager introduced by Kubernetes, is that k8s applications, which are typically comprised of deployment, services, et cetera, have gotten very complex. And when installing these applications, they're delivered in their own namespace, which makes it easier to encapsulate the application in one single spot in your Kubernetes cluster, all in just a single namespace.

When you're done using the application, you can just delete the namespace.

Interacting with namespaces is very straightforward. Let's discuss the basic commands related to them. To just get all your existing namespaces, you can just do a kubectl get namespaces.
To create one, all you have to do is do a kubectl create namespace followed by the name you want to use.
Similarly, to delete the namespace, it's a kubectl delete namespace followed by the namespace you'd like to delete.

When deploying a specific resource, like a deployment to a specific namespace, just add the -n namespace-name, and the resource will exist in that specific namespace.

## Monitoring & Logging

Once you have your infrastructure, and your applications have been deployed successfully, you've run into your next challenge.

Are they operating correctly? Have you been seeing any errors? Are they even online? DevOps practices of monitoring and logging can help you answer these specific questions.

Let's take a look at how to do this specifically from a Kubernetes perspective.

First, let's tackle logging. If your application isn't outputting logs it probably should. Fellow LinkedIn author, and Agile Admin, Ernest Mueller, wrote a great article on logging for success that developers should read. True story. He wrote this article after he was trying to debug issues with an application that I wrote, looked at some good and bad things that I'd done in my logs, and the rest is history. From a Kubernetes perspective, starting out it's better for your applications to be running in a pod to write logs to standard out. This is because the Kubernetes would automatically pick up the logs and show you anything in the log info when you do a kubectl logs command to go and fetch the logs. This is really useful when you're doing development. Once your application is running in the staging or production environment, you might consider using a logging platform like Elasticsearch and Kibana with the logs being shipped to them from pods using Fluentd or Filebeats, which is the new version of logstash.

You would typically run a deployment for your Elasticsearch and Kibana instance outside of your application. The Elasticsearch endpoint needs to be accessible to pods in the cluster, and the Kibana instance should be exposed as a service so that you can see your log information in the Kibana user interface. Then, in your application deployment, you want the log shipper, like Fluentd, logstash, or Filebeats to gather log data and periodically send it to the Elasticsearch instance.

I've included some docs for you to get started in the course exercise files that explain this process more in detail, so take a look.

From a monitoring perspective, we have a few things we'd like to monitor, node health, the health of Kubernetes, and application health and also metrics for applications. For node and Kubernetes health, the combination of two open-source projects, cAdvisor and Heapster, might be one way to solve this problem. cAdvisor is an open-source resource usage collector that was built for containers specifically. It auto-discovers all containers in the given node and collects CPU, memory, file system, and network usage statistics. cAdvisor also provides overall machine usage by analyzing the root container on the machine.

Heapster aggregates monitoring data across all of your nodes in your Kubernetes cluster. Just like in application, Heapster runs as a pod in deployment in the cluster. The Heapster pod queries usage information from the node's kubelets, which in turn queries that data from cAdvisor. Heapster groups the information by pod along with, including any relevant labels.

Finally, your application might want to send application metrics. For example, the number of successful logins per hour. To ingest this, you can use an open-source framework called Prometheus. Prometheus is a time series database with a great query language that works well for application-specific metrics and also can be used from an alerting standpoint. You can instrument your application to save application monitoring data at a slash metrics endpoint that Prometheus queries in a timely manner. Prometheus, Heapster, and cAdvisor are typically linked to Grafana, which is an open-source tool to visualize monitoring data.

One last thing on monitoring and logging. The architectures I've described in this section are popular architectures today, but this space is still pretty young and is rapidly changing. My recommendations for logging and monitoring are: 1. Read the docs for the projects. Setting up logging and monitoring is not a trivial task today, but there's a lot of work that's being done in the user experience in this space and setup of the tools to make things easier. 2. I also have not covered enterprise tooling like Datadog or Riverbed, for example. If you're already using one of these tools for your infrastructure, take a look at what Kubernetes support they already have and use them where applicable. No point in reinventing the wheel when you don't have to.

## Authentication and authorization

Authentication and authorization are two of the most common topics that arise when folks are trying to integrate Kubernetes into their infrastructure. In this section, I'll go over what these features are, and give you a working understanding of how authentication and authorization work.

From an architecture perspective, users who are trying to access the Kubernetes API, via the kubectl command, first have to be authenticated to access the API. And then authorized to run specific actions. Occasionally, users will also need to have admission control to approve or reject a request.

First off, we need to understand what a user means from a Kubernetes context. There are actually two kinds of users.

Normal users, like you and me, and service accounts which are internal users to the system. We typically think of normal users as users who are in an LDAP or an SSO system in our enterprises. From a Kubernetes perspective, these users are managed outside of Kubernetes.

Service accounts are managed by the Kube API server, bound to a specific namespace, and tied to credentials managed in secrets. There are four pieces of information that define a user.

The username, which is basically a string. For example, Karthik or Karthik@example.com.

A UID, or a unique ID, which is an identifier that is more consistent and unique than the username.

A group, which is a string that associates users with a set of commonly grouped users. These are used later on the by authorization model.

And extra fields which is basically a map of strings that holds additional information used by the authorization system. Authentication in Kubernetes defines whether a user has access to communicate with the Kube API server. And authorization defines whether a user has actual permissions to perform specific actions. There are a number of ways you can authenticate. The entire list can be found in the Kubernetes documentation but we'll look at the four most popular modules that enterprises use today. Client certs, static tokens, OpenID connect, or the webhook mode.

Client cert authentication is enabled by passing the client ca file option to the API server. The reference file must contain certificate authorities to validate client certificates passed to the API server. If a client cert is presented and verified, the common name of the client certificate is used as the username for the request.

This is a straight forward way to manage Kubernetes if you're comfortable with handling certificate managements in your org. The API server reads the bare tokens from a file when given the `--token-auth-file` option on the command line. The token auth file is a CSV file with four columns: token, username, user UID, followed by optional group names as shown in the example. The caveat to this method is that these tokens last indefinitely and you're required to restart the API server for any changes in tokens to take place.

The static password file is similar to this method but the values are passed as basic auth parameters. The benefit of this method, is that it's very simple and easy to manage a small batch of users this way. For larger organizations that already have oAuth, such as Google, or Azure Active Directory, you can configure the OpenID connect tokens to authenticate against Kubernetes. The details of this are complex and I'd recommend reading the docs for this method.

And finally, there's authentication using webhook tokens. This is one of the most common methods that's used by a number of organizations who want to have the users interacting with Kubernetes but also manage tokens in an easier way. Using this method, the Kube API server makes a request to an API that's defined by you to authenticate. The remote API decides whether a token passed to it is a valid token or not, and then responds back to the server.

On the authorization front, there are three common ways to perform authorizations. ABAC, RBAC, or Webhook. Let's see what these are.

ABAC, or attribute based access control, defines an access control paradigm whereby access rights are granted to users through the use of policies that combine attributes together. The ABAC file defines what access a specific user might have to all resources. In the example config shown, Karthik has master access to all attributes, whereas the user Carisa only has read access to all the repos and name spaces.

RBAC is role based access control. This is _the most common authorization mechanism_ used in Kubernetes and a lot of applications end up using RBAC to authorize their service accounts. I would recommend that you turn on this functionality on your KubeAPI server even if you're using another authorization mechanism, because you'll end up using something that will require RBAC being installed. RBAC depends on roles and cluster roles. These are rules that represent a set of permissions. A role can be defined within the namespace with a role or a clusterwide with a cluster role. In this example, we see that a role is in the default namespace that allows read access to all pods. Role bindings grant permissions defined in a role to users. They hold the users or group as a reference to the role being granted. Permissions can then be granted within a namespace with a role binding or cluster wide with a cluster role binding. In the example shown, the user Karthik can read pods in the default namespace.

The webhook mode for authorization, like the authentication webhook mode, allows you to define what permissions are allowed for a specified user. The Kube API server will send a request with the user and resource attribute data to a remote server that you define, that interprets the request and defines whether a request is allowed or not. This method works really well if you're trying to integrate with a third party authorization system, or if you want a complex set of rules.
