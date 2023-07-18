#!/bin/bash
github(){
    #git clone https://github.com/DaggupatiPavan/oai-cn5g-fed.git
    echo "cloned succesfully"
}

buildImage(){
    # Versioning
	TAGS=$(echo "$TAG + 0.1" | bc)
	sed -i "s/TAG=$TAG/TAG=$TAGS/g" /etc/environment
    # Code to build the Docker image
    docker build --target oai-amf --tag pavan176/oai-amf:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-amf/docker/Dockerfile.amf.ubuntu --build-arg BASE_IMAGE=ubuntu:focal /home/cloudawspoc/oai-cn5g-fed/component/oai-amf
    docker build --target oai-smf --tag pavan176/oai-smf:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-smf/docker/Dockerfile.smf.ubuntu --build-arg BASE_IMAGE=ubuntu:22.04 /home/cloudawspoc/oai-cn5g-fed/component/oai-smf
    docker build --target oai-nrf --tag pavan176/oai-nrf:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-nrf/docker/Dockerfile.nrf.ubuntu --build-arg BASE_IMAGE=ubuntu:jammy /home/cloudawspoc/oai-cn5g-fed/component/oai-nrf
    docker build --target oai-spgwu-tiny --tag pavan176/oai-spgwu-tiny:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-upf-equivalent/docker/Dockerfile.ubuntu --build-arg BASE_IMAGE=ubuntu:20.04 /home/cloudawspoc/oai-cn5g-fed/component/oai-upf-equivalent
    docker build --target oai-ausf --tag pavan176/oai-ausf:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-ausf/docker/Dockerfile.ausf.ubuntu /home/cloudawspoc/oai-cn5g-fed/component/oai-ausf
    docker build --target oai-udm --tag pavan176/oai-udm:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-udm/docker/Dockerfile.udm.ubuntu /home/cloudawspoc/oai-cn5g-fed/component/oai-udm
    docker build --target oai-udr --tag pavan176/oai-udr:$TAG --file /home/cloudawspoc/oai-cn5g-fed/component/oai-udr/docker/Dockerfile.udr.ubuntu /home/cloudawspoc/oai-cn5g-fed/component/oai-udr
}

vulnerabilityScan(){
    # Code to scan the Docker image for vulnerabilities
    for i in 'amf' 'smf' 'nrf' 'spgwu-tiny' 'ausf' 'udm' 'udr'
    do
        grype docker:pavan176/oai-$i:$TAG > /home/cloudawspoc/grype_results/oai-$i:$TAG
    done
}

push_Image_To_DockerHub(){
    # Code to push the Docker image to Docker Hub
    for i in 'amf' 'smf' 'nrf' 'spgwu-tiny' 'ausf' 'udm' 'udr'
    do
        docker push pavan176/oai-$i:$TAG
    done
}

deploy_Images_Using_Flux(){
    # Code to deploy the Docker images using Flux
    echo "deploy"
}

# Call the functions in the desired order
github
buildImage
vulnerabilityScan
#push_Image_To_DockerHub
#deploy_Images_Using_Flux
