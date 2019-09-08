provider "aws" {
    version = "~> 2.10"
    profile = "default"
    region  = var.region
}

data "aws_ami" "ubuntu" {
    most_recent = true
    owners = ["aws-marketplace"]
    filter {
        name   = "name"
        values = ["*ubuntu-bionic-18.04-amd64-server*"]
    }
}

resource "aws_key_pair" "my_key" {
    key_name = "dev-key"
    public_key = var.ssh_key_public
}

resource "aws_instance" "minikube" {
    ami = "${data.aws_ami.ubuntu.id}"
    instance_type = "t2.large"
    key_name = "${aws_key_pair.my_key.key_name}"
  
    root_block_device {
        delete_on_termination = "true"
    }

    tags = {
        Name = "Minikube"
    }

    provisioner "file" {
        source = "../../examples/learning-k8s/Learning_K8s.zip"
        destination = "~/Learning_K8s.zip"
        connection {
            user = "ubuntu"
            host = "${aws_instance.minikube.public_ip}"
            agent = "true"
        }
    }

    provisioner "remote-exec" {
        inline = [
            #"curl -LO https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl",
            #"chmod +x ./kubectl",
            #"sudo mv ./kubectl /usr/local/bin/kubectl",
            "sudo apt-get update",
            # "sudo apt-get install docker.io -y",
            # "sudo apt-get install unzip -y",
            # "curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64",
            # "chmod +x minikube",
            # "sudo mv minikube /usr/local/bin/minikube",
            # "minikube version",
            # "sudo systemctl enable kubelet.service",
            # "sudo systemctl enable docker.service",
            # "sudo minikube start --vm-driver=none",
            # "sudo minikube status",
            "unzip Learning_K8s.zip"
        ]
        connection {
            user = "ubuntu"
            host = "${aws_instance.minikube.public_ip}"
            agent = "true"
        }  
    }
}

resource "aws_eip" "ip" {
    instance = aws_instance.minikube.id
    tags = {
        Name = "Minikube EIP"
    }
}

output "ip" {
    value = aws_eip.ip.public_ip
}