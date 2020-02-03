#Readme

Required installations:
Docker (Community Edition, Stable build): https://www.docker.com/community-edition#/download
kubectl: https://kubernetes.io/docs/tasks/tools/install-kubectl/
Virtualbox: https://www.virtualbox.org/wiki/Downloads
minikube: https://github.com/kubernetes/minikube/releases/tag/v0.25.2

For instance, my versions are as follows:
Docker Version:
```
: docker version
Client:
 Version:	18.03.0-ce
 API version:	1.37
 Go version:	go1.9.4
 Git commit:	0520e24
 Built:	Wed Mar 21 23:06:22 2018
 OS/Arch:	darwin/amd64
 Experimental:	false
 Orchestrator:	swarm

Server:
 Engine:
  Version:	18.03.0-ce
  API version:	1.37 (minimum version 1.12)
  Go version:	go1.9.4
  Git commit:	0520e24
  Built:	Wed Mar 21 23:14:32 2018
  OS/Arch:	linux/amd64
  Experimental:	true
: 
```

Kubectl version:
```
: kubectl version
Client Version: version.Info{Major:"1", Minor:"9", GitVersion:"v1.9.6", GitCommit:"9f8ebd171479bec0ada837d7ee641dec2f8c6dd1", GitTreeState:"clean", BuildDate:"2018-03-21T15:21:50Z", GoVersion:"go1.9.3", Compiler:"gc", Platform:"darwin/amd64"}
Server Version: version.Info{Major:"", Minor:"", GitVersion:"v1.9.4", GitCommit:"bee2d1505c4fe820744d26d41ecd3fdd4a3d6546", GitTreeState:"clean", BuildDate:"2018-03-21T21:48:36Z", GoVersion:"go1.9.1", Compiler:"gc", Platform:"linux/amd64"}
```

Virtualbox version: 
```
Version 5.2.8 r121009 (Qt5.6.3)
```

Minikube:
```
: minikube version
minikube version: v0.25.2
```

12-factor app

https://12factor.net

First created for SaaS in heroku

1 codebase tracked in version control with many deploies
2 dependences are explicitly declared and isolated (don't copy past)
3 configuration stored in the environment
4 backing services are treated as attanched resources
5 build, release, run
6 Processes - execute the app as a stateless process
7 Port bindings
8,9,10 concurrency, disposability, dev/prod parity
11,12 log management & admin tasks
log event streams, admin treated the same as the app

## Microservice building blocks

Codebases (git, etc or container repos)

1. push code into source control
2. auto build and test
3. build container image and push to image repo

Containers store corp info. 

App dependencies

Apps modeled in k9s as deployments and pods
single pod can have many containers inside
commonly seen as sidecar pattern

Dev vs. Prod

Small footprint might use namespaces with different credentials for dev/ staging/ prod
Large footprints use unique k8s for each type to spread risk during test deployment

Admin
Tasks run as processes the same as the application
Containers run as k8s job / cron
Or as a separate deployment (with auth and access rules)

Deployment patterns

Apps always have associated config to make the app work
K8s, has 2 options for this to make app code distinct from config
config maps for metadata, etc (generic info)
secrets: passwords, api keys, etc

fed to the pod as file or env vars

Secrets are good, but some like extra layers like vault

Build, release, run

tag containers with specific version or build number
Don't use 'latest'

Processes and port bindings

Keep app stateless
dont rely on sticky sessions
Don't depend on any request going to the same container or server

Statless == deployments and pods where traffic can be sent to any responding pod

StatefulSets == persistent storage like mysql shard

Port bindings -> part of the pod config by default via config files

Runtime patterns

everything is a service with config in configmap / secret

create new db making sure it's ready
Update config with info passed
kill pods using old db version
On start the new pods get the new config and start directly

An overloaded pod is easy to scale up.

disposability

max ability to startup and run efficiently having most of the tooling
built inside the image

K9s, manages containers in pods, which are managed in replicasets, on failure pods get restarted automaticly

Logging

default treats logs as streams via log router to a search service (ELK or datadog)


