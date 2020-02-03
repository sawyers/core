Daemonsets: A DaemonSet ensures that all Nodes run a copy of a Pod. As nodes are added to the cluster, Pods are added to them. Examples of a daemon set would be running your logging or monitoring agent on your nodes.

In this example, I will just run a simple busybox image as a daemonset.

`kubectl create -f daemonset.yaml`

`kubectl get daemonsets`

in infrastrcture development you can add a node selector for develop
You can check against node lables to see where they would deploy, in minikube minikube is develop, in real deployments you would have nodes set aside for specific reasons by label.

The infra value in the yaml config files selects by label where something would be deployed.

If no nodes match the requested tab the deploy will run, but not have any matching node to start pods against.

Statefulsets Manages the deployment and scaling of a set of Pods, and provides guarantees about the ordering and uniqueness of these Pods. Unlike a Deployment, a StatefulSet maintains a sticky identity for each of their Pods.

pod Affinity is part of the stateful-ness. Common use would have multiple pods 
