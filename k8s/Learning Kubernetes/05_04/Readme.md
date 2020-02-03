# Working with secrets

## Chapter Goals
1. Learn how to declare a secret
2. Understand how to add a secret to a deployment

### Learn how to declare a secret
Just like configuration data, applications might also require other data that might be of more sensitive in nature- for example database passwords, or API tokens. Passing these in the yaml for a deployment or pod would make them visible to everyone.

In these usecases, use a secret to encapsulate sensitive data.

To create a secret: `kubectl create secret generic apikey --from-literal=api_key=123456789`

Notice that we can't read the value of the secret directly:
`kubectl get secret apikey -o yaml`

The output data is encoded in base64 encoding

### Understand how to add a secret to a deployment

Adding a secret to a deployment is similar to what we did for configmaps. You can add a secret to the env portion, and start up the deployment with:
`kubectl create -f secretreader-deployment.yaml`

looking inside the pod in thise case is created to echo the decoded secret to logs for the example

kubectl logs secretreader-d7568bbb7-hx4c6
api_key passed via env variable was: '123456789'
api_key passed via env variable was: '123456789'
api_key passed via env variable was: '123456789'
api_key passed via env variable was: '123456789'