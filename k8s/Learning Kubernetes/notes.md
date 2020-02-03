# Linkedin Learning - Learning Kubernetes

## 1 Containerization with k8s

- Features
  - Open source for all sizes to automating service lifecycle from deploy to management
  - Multi-host container scheduling, done by kube-scheduler to assing pods as needed
  - The Pods can be horizontally scaled via an API. Flexibility and Modularization. Kubernetes has a plug-and-play architecture
  - There are specific add-ons for network drivers, service discovery, container runtime, visualization, and command.
  - Two features that allow Kubernetes Clusters to scale are Registration and Discovery
  - Application upgrades are supported out of the box, as well as application rollbacks
  - Secrets are mounted as data volumes or environment variables, and they are also specific to a single namespace.

## 2 Terminology

- master node has API server, scheduler, controller mgr (node controller, replication, endpoints, service act & tokens, etcd [cluster db] for jobs, status, etc)
  - interacted with by kubectl
- work nodes via kubelet to run pods, manage nodes, etc. Works with docker in most cases. Also uses kube-proxy
- Docker on nodes runs containers called pods and they are the smallest unit. Kubelet manages and routes work on the node between pods and the proxy handles internet access if needed.

### Nodes and pods

- Master controlls the cluster built of nodes
- a node can be physical or virtual and must have kubelet, container mgt, kube-proxy and supervisord
- have at least 3 nodes for production
- minikube for local dev
- Pods is the simplest unit, you can crud pods and is a running process
- Each pod has the docker application container, storage, IP and options of how the containers should run. A pod may be multiple docker containers (eg. service + health) but are the smallest unit of deployment, a single instance of an app.
- Pods are designed to be ephemeral, disposable entities.
- If a pod dies it doesn't get rescheduled
- a pod can be run on its own for dev/test but will lack a contr----- Updated Jul 2, 2019 9:30:47 AM -----oller, so if it dies or exits it will not restart.  The controllers add management concepts to pods.
- States: Pending, Running, Succeeded, Failed, CrashLoopBackOff (failed to start and k8s is looping attempts to restart the pod.)

### Deployments

- Controllers provide app reliability, scaling, load balancing
  - ReplicaSet - ensure pods are running at all times at defined number of pods and is part of a deployment
  - describes updates of pods and ReplicaSets
  - Deployment -> ReplicaSet -> pod; allows easy rollback on failed update
    - Pod management via ReplicaSet to deploy / monitor pods as a single unit
    - Scaling ReplicaSet to handle load balancing / scale up or down
    - Pause / resume of a deployment for larger change sets; only pauses the update, not the service
    - Status / health
  - Replication (replaced by deployments)
  - DaemonSets - version control of pods
    - Job control, state of the job, unique run of processes
    - Services of network connectivity between deployments
    - Allows pod sets to communicate (internal / external public endpoints) AKA NodePort
    - Load Balancers
  - Labels are key/value to organize and are unique per
    - release: state
    - env: dev/qa
    - tier: front/back
  - Selectors are set based or equality based
    - used to list and filter objects
  - namespaces allow access to teams with accountability or divide clusters between users and scope for names (unique in a namespace)

### Kubelet and proxy

- kubelet talks to the controller via API, executes pods via container engine, mounts volumes and manages secrets and runs pod health checking
- Runs via podspec (yaml) kubelet manages pods based on the spec but does not manage pods started by hand (see above). Only pods created via the API server are managed.
- Can be managed by REST, but is rare
- Proxy manages processes that run on the nodes, manages services defined for each node including round-robin load balancing and manage service cluster IP's / ports
- User space, iptables, ipvs modes, user space is most common.
- Services are defined against API server, proxy monitors the api for changes
- proxy opens random port on the local node for each service and connections made the the port are proxied to one of the corresponding back-end pods

## 3 Lab

### Using minikube with virtual box

```bash
$ minikube start
😄  minikube v1.2.0 on darwin (amd64)
👍  minikube will upgrade the local cluster from Kubernetes 1.13.4 to 1.15.0
💿  Downloading Minikube ISO ...
 129.33 MB / 129.33 MB [============================================] 100.00% 0s
🔥  Creating virtualbox VM (CPUs=2, Memory=2048MB, Disk=20000MB) ...
🐳  Configuring environment for Kubernetes v1.15.0 on Docker 18.09.6
💾  Downloading kubeadm v1.15.0
💾  Downloading kubelet v1.15.0
🚜  Pulling images ...
🚀  Launching Kubernetes ...
⌛  Verifying: apiserver proxy etcd scheduler controller dns
🏄  Done! kubectl is now configured to use "minikube"

$ kubectl get nodes
NAME       STATUS   ROLES    AGE   VERSION
minikube   Ready    master   15m   v1.15.0

$ kubectl run hw --image=karthequian/helloworld --port=80
deployment.apps/hw created

$ kubectl get deployments
NAME   READY   UP-TO-DATE   AVAILABLE   AGE
hw     1/1     1            1           91s

$ kubectl get rs
NAME            DESIRED   CURRENT   READY   AGE
hw-5ccdc9995d   1         1         1       2m12s

$ kubectl get pods
NAME                  READY   STATUS    RESTARTS   AGE
hw-5ccdc9995d-7zf6q   1/1     Running   0          2m35s

$ kubectl expose deployment hw --type=NodePort
service/hw exposed

$ kubectl get services
NAME         TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)        AGE
hw           NodePort    10.111.48.86   <none>        80:31708/TCP   13s
kubernetes   ClusterIP   10.96.0.1      <none>        443/TCP        20m

# open the service in a browser
$ minikube service hw

$ kubectl get all
NAME                      READY   STATUS    RESTARTS   AGE
pod/hw-5ccdc9995d-7zf6q   1/1     Running   0          17m

NAME                 TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)        AGE
service/hw           NodePort    10.111.48.86   <none>        80:31708/TCP   13m
service/kubernetes   ClusterIP   10.96.0.1      <none>        443/TCP        34m

NAME                 READY   UP-TO-DATE   AVAILABLE   AGE
deployment.apps/hw   1/1     1            1           17m

NAME                            DESIRED   CURRENT   READY   AGE
replicaset.apps/hw-5ccdc9995d   1         1         1       17m

# Get the podspec from a running deployment
$ kubectl get deployment/hw -o yaml

# create one with a helm file
$ kubectl create -f 03_04/helloworld-all.yml
deployment.apps/helloworld-all-deployment created
service/helloworld-all-service created

$ kubectl get services
NAME                     TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)        AGE
helloworld-all-service   LoadBalancer   10.107.151.245   <pending>     80:31684/TCP   34s
hw                       NodePort       10.111.48.86     <none>        80:31708/TCP   22m
kubernetes               ClusterIP      10.96.0.1        <none>        443/TCP        42m

# scaling pods / deployments with replica sets
$ kubectl get rs
NAME                                   DESIRED   CURRENT   READY   AGE
helloworld-all-deployment-78cc88c7d7   1         1         1       4m41s
helloworld-deployment-78cc88c7d7       1         1         1       2m43s
hw-5ccdc9995d                          1         1         1       29m

$ kubectl scale --replicas=3 deploy/helloworld-deployment
deployment.extensions/helloworld-deployment scaled

$ kubectl get deployments
NAME                        READY   UP-TO-DATE   AVAILABLE   AGE
helloworld-all-deployment   1/1     1            1           6m34s
helloworld-deployment       3/3     3            3           4m36s
hw                          1/1     1            1           31m

$ kubectl get pods
NAME                                         READY   STATUS    RESTARTS   AGE
helloworld-all-deployment-78cc88c7d7-qvrqq   1/1     Running   0          6m52s
helloworld-deployment-78cc88c7d7-5sg6d       1/1     Running   0          48s
helloworld-deployment-78cc88c7d7-fxzmd       1/1     Running   0          48s
helloworld-deployment-78cc88c7d7-qbblj       1/1     Running   0          4m54s
hw-5ccdc9995d-7zf6q                          1/1     Running   0          32m
```

## 4 Production ready

### Sample deploy with services, helloworld-pod-with-labels

```bash
$ kubectl create -f helloworld-pod-with-labels.yml
pod/helloworld created

$ kubectl get pods
NAME         READY   STATUS    RESTARTS   AGE
helloworld   1/1     Running   0          4m49s

$ kubectl get pods --show-labels
NAME         READY   STATUS    RESTARTS   AGE     LABELS
helloworld   1/1     Running   0          5m40s   application_type=ui,author=karthequian,env=production,release-version=1.0

$ kubectl label po/helloworld app=helloworldapp --overwrite
pod/helloworld labeled

$ kubectl get pods --show-labels
NAME         READY   STATUS    RESTARTS   AGE     LABELS
helloworld   1/1     Running   0          6m34s   app=helloworldapp,application_type=ui,author=karthequian,env=production,release-version=1.0

$ kubectl label pod/helloworld app-
pod/helloworld labeled

$ kubectl get pods --show-labels
NAME         READY   STATUS    RESTARTS   AGE     LABELS
helloworld   1/1     Running   0          7m21s   application_type=ui,author=karthequian,env=production,release-version=1.0

$ kubectl delete pod/helloworld
```

### Search by labels

Filter the pods output by labels

```bash
$ kubectl create -f sample-infrastructure-with-labels.yml

$ kubectl get pods --show-labels
NAME               READY   STATUS    RESTARTS   AGE    LABELS
cart-dev           1/1     Running   0          3m3s   application_type=api,dev-lead=carisa,env=development,release-version=1.0,team=ecommerce
cart-prod          1/1     Running   0          3m3s   application_type=api,dev-lead=carisa,env=production,release-version=1.0,team=ecommerce
cart-staging       1/1     Running   0          3m3s   application_type=api,dev-lead=carisa,env=staging,release-version=1.0,team=ecommerce
...

# only production pods
$ kubectl get pods --selector env=production
NAME            READY   STATUS    RESTARTS   AGE
cart-prod       1/1     Running   0          3m46s
catalog-prod    1/1     Running   0          3m46s
homepage-prod   1/1     Running   0          3m46s
login-prod      1/1     Running   0          3m46s
ordering-prod   1/1     Running   0          3m46s
quote-prod      1/1     Running   0          3m46s
social-prod     1/1     Running   0          3m46s

# only pods run by carisa
$ kubectl get pods --selector dev-lead=carisa
NAME           READY   STATUS    RESTARTS   AGE
cart-dev       1/1     Running   0          4m51s
cart-prod      1/1     Running   0          4m51s
cart-staging   1/1     Running   0          4m51s
social-dev     1/1     Running   0          4m51s

# pods run by carisa and in staging
$ kubectl get pods --selector dev-lead=carisa,env=staging
NAME           READY   STATUS    RESTARTS   AGE
cart-staging   1/1     Running   0          5m32s

# pods not run by karthik and in staging
$ kubectl get pods --selector dev-lead!=karthik,env=staging
NAME               READY   STATUS    RESTARTS   AGE
cart-staging       1/1     Running   0          6m14s
catalog-staging    1/1     Running   0          6m14s
login-staging      1/1     Running   0          6m14s
ordering-staging   1/1     Running   0          6m14s
quote-staging      1/1     Running   0          6m14s
social-staging     1/1     Running   0          6m14s

# any pod between release 1.0 and 2.0
$ kubectl get pods -l 'release-version in (1.0,2.0)'
NAME               READY   STATUS    RESTARTS   AGE
cart-dev           1/1     Running   0          7m13s
cart-prod          1/1     Running   0          7m13s
cart-staging       1/1     Running   0          7m13s
login-dev          1/1     Running   0          7m13s
login-prod         1/1     Running   0          7m13s
login-staging      1/1     Running   0          7m13s
ordering-dev       1/1     Running   0          7m13s
ordering-prod      1/1     Running   0          7m13s
ordering-staging   1/1     Running   0          7m13s
quote-dev          1/1     Running   0          7m13s
quote-prod         1/1     Running   0          7m13s
quote-staging      1/1     Running   0          7m13s
social-dev         1/1     Running   0          7m13s
social-prod        1/1     Running   0          7m13s
social-staging     1/1     Running   0          7m13s

# any pod not between 1.0 and 2.0
$ kubectl get pods -l 'release-version notin (1.0,2.0)'
NAME               READY   STATUS    RESTARTS   AGE
catalog-dev        1/1     Running   0          7m43s
catalog-prod       1/1     Running   0          7m43s
catalog-staging    1/1     Running   0          7m43s
homepage-dev       1/1     Running   0          7m44s
homepage-prod      1/1     Running   0          7m43s
homepage-staging   1/1     Running   0          7m44s

# delete all pods run by karthik
$ kubectl delete pods -l dev-lead=karthik
pod "homepage-dev" deleted
pod "homepage-prod" deleted
pod "homepage-staging" deleted
```
### Health check

in the cluster you can define readiness and liveliness checks for each service.  Thing like checking for a service started or a response from a web server might be common.

each probe can set a wait time and number of retries before it is considered failed.  A failure in readyness will prevent the deploy from being ready while a liveliness probe will trigger restarts of the container to try and get it healthy.

### Service updates

## 5 