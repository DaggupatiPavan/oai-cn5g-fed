#!/bin/bash
github(){
    #git clone https://github.com/DaggupatiPavan/oai-cn5g-fed.git
    echo "cloned succesfully"
}

buildImage(){
    # Code to build the Docker image
    docker build --target oai-amf --tag pavan176/oai-amf:v1 --file component/oai-amf/docker/Dockerfile.amf.ubuntu --build-arg BASE_IMAGE=ubuntu:focal component/oai-amf
    docker build --target oai-smf --tag pavan176/oai-smf:v1 --file component/oai-smf/docker/Dockerfile.smf.ubuntu --build-arg BASE_IMAGE=ubuntu:22.04 component/oai-smf
    docker build --target oai-nrf --tag pavan176/oai-nrf:v1 --file component/oai-nrf/docker/Dockerfile.nrf.ubuntu --build-arg BASE_IMAGE=ubuntu:jammy component/oai-nrf
    docker build --target oai-spgwu-tiny --tag pavan176/oai-spgwu-tiny:v1 --file component/oai-upf-equivalent/docker/Dockerfile.ubuntu --build-arg BASE_IMAGE=ubuntu:20.04 component/oai-upf-equivalent
    docker build --target oai-ausf --tag pavan176/oai-ausf:v1 --file component/oai-ausf/docker/Dockerfile.ausf.ubuntu component/oai-ausf
    docker build --target oai-udm --tag pavan176/oai-udm:v1 --file component/oai-udm/docker/Dockerfile.udm.ubuntu component/oai-udm
    docker build --target oai-udr --tag pavan176/oai-udr:v1 --file component/oai-udr/docker/Dockerfile.udr.ubuntu component/oai-udr
}

vulnerabilityScan(){
    # Code to scan the Docker image for vulnerabilities
    for i in 'amf' 'smf' 'nrf' 'spgwu-tiny' 'ausf' 'udm' 'udr'
    do
        grype docker:pavan176/oai-$i:v1 > ~/oai-$i:v1
    done
}

push_Image_To_DockerHub(){
    # Code to push the Docker image to Docker Hub
    for i in 'amf' 'smf' 'nrf' 'spgwu-tiny' 'ausf' 'udm' 'udr'
    do
        docker push pavan176/oai-$i:v1
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
push_Image_To_DockerHub
#deploy_Images_Using_Flux
