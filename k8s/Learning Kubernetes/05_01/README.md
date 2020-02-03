# More complicated examples

deploy guest book
`kubectl create -f guestbook.yaml`

multiple deployments and services, which is common

```bash
kubectl get deployments
NAME           READY   UP-TO-DATE   AVAILABLE   AGE
frontend       0/3     3            0           56s
redis-master   0/1     1            0           56s
redis-slave    0/2     2            0           56s
```

Full deploy may take several minutes if you don't have the containers already downloaded or are on a slower connection.

kubectl get services
NAME           TYPE        CLUSTER-IP       EXTERNAL-IP   PORT(S)        AGE
frontend       NodePort    10.96.231.189    <none>        80:30272/TCP   3m5s
kubernetes     ClusterIP   10.96.0.1        <none>        443/TCP        34m
redis-master   ClusterIP   10.107.168.224   <none>        6379/TCP       3m5s
redis-slave    ClusterIP   10.104.105.95    <none>        6379/TCP       3m5s

common request for GUI front end for clusters, this can be eabled via default addons

minikube addons list
- addon-manager: enabled
- dashboard: disabled
- default-storageclass: enabled
- efk: disabled
- freshpod: disabled
- gvisor: disabled
- heapster: disabled
- ingress: disabled
- logviewer: disabled
- metrics-server: disabled
- nvidia-driver-installer: disabled
- nvidia-gpu-device-plugin: disabled
- registry: disabled
- registry-creds: disabled
- storage-provisioner: enabled
- storage-provisioner-gluster: disabled

`minikube dashboard`
🔌  Enabling dashboard ...
🤔  Verifying dashboard health ...
🚀  Launching proxy ...
🤔  Verifying proxy health ...
🎉  Opening http://127.0.0.1:58534/api/v1/namespaces/kube-system/services/http:kubernetes-dashboard:/proxy/ in your default browser..

Information about memory use is also very important
minikube addons enable heapster
✅  heapster was successfully enabled

kubectl get pods --all-namespaces
NAMESPACE     NAME                                    READY   STATUS    RESTARTS   AGE
default       frontend-678d98b8f7-fbg5n               1/1     Running   0          6m32s
default       frontend-678d98b8f7-kk2jl               1/1     Running   0          6m32s
default       frontend-678d98b8f7-vhnxn               1/1     Running   0          6m32s
default       redis-master-77bb4946d6-9hphc           1/1     Running   0          6m32s
default       redis-slave-84548fdbc-5jddk             1/1     Running   0          6m32s
default       redis-slave-84548fdbc-vz46n             1/1     Running   0          6m32s
kube-system   coredns-5c98db65d4-ksdxt                1/1     Running   2          51d
kube-system   coredns-5c98db65d4-r7qdc                1/1     Running   2          51d
kube-system   etcd-minikube                           1/1     Running   1          51d
kube-system   kube-addon-manager-minikube             1/1     Running   1          51d
kube-system   kube-apiserver-minikube                 1/1     Running   1          51d
kube-system   kube-controller-manager-minikube        1/1     Running   1          51d
kube-system   kube-proxy-v856j                        1/1     Running   1          51d
kube-system   kube-scheduler-minikube                 1/1     Running   1          51d
kube-system   kubernetes-dashboard-7b8ddcb5d6-tvpfw   1/1     Running   0          81s
kube-system   storage-provisioner                     1/1     Running   3          51d

that creates the new kube-system namespace including things related to management with output baked into 
the k8s dashboard like CPU and memory use.


