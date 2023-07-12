"""
 Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 contributor license agreements.  See the NOTICE file distributed with
 this work for additional information regarding copyright ownership.
 The OpenAirInterface Software Alliance licenses this file to You under
 the OAI Public License, Version 1.1  (the "License"); you may not use this file
 except in compliance with the License.
 You may obtain a copy of the License at

   http://www.openairinterface.org/?page_id=698

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
-------------------------------------------------------------------------------
 For more information about the OpenAirInterface (OAI) Software Alliance:
   contact@openairinterface.org
"""

import argparse
import os
import re
import subprocess
import sys
import time

def main() -> None:
    args = _parse_args()
    status = generic_deployment(args.tag)
    sys.exit(status)

def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Sanity Check')

    parser.add_argument(
        '--tag', '-t',
        action='store',
        required=True,
        help='Image Tag in image-name:image tag format',
    )
    return parser.parse_args()

def generic_deployment(tag):
    # First detect which docker/podman command to use
    cli = ''
    cmd = 'which podman || true'
    podman_check = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if re.search('podman', podman_check.strip()):
        cli = 'sudo podman'
    if cli == '':
        cmd = 'which docker || true'
        docker_check = subprocess.check_output(cmd, shell=True, universal_newlines=True)
        if re.search('docker', docker_check.strip()):
            cli = 'docker'
    if cli == '':
        print ('No docker / podman installed: quitting')
        return -1

    status = 0
    if cli == 'docker':
        infos = tag.split(':')
        cmd = 'sed -e "s@NEF_IMAGE_TAG@' + infos[1] + '@" ci-scripts/docker-compose/docker-compose.tplt > ci-scripts/docker-compose/docker-compose.yaml'
        print (cmd)
        subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        cmd = 'cd ci-scripts/docker-compose && docker-compose up -d'
        print (cmd)
        upStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(upStatus.strip()).split('\n'):
            print(line)
        time.sleep(20)
        cmd = 'docker inspect --format="STATUS: {{.State.Health.Status}}" cicd-oai-nef'
        print (cmd)
        healthStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(healthStatus.strip()).split('\n'):
            print(line)
            if re.search('STATUS:', line):
                if re.search('STATUS: healthy', line):
                    status = 0
                else:
                    status = -1
        cmd = 'docker logs cicd-oai-nef'
        print (cmd)
        logStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(logStatus.strip()).split('\n'):
            print(line)
        time.sleep(5)
        cmd = 'cd ci-scripts/docker-compose && docker-compose down'
        print (cmd)
        downStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(downStatus.strip()).split('\n'):
            print(line)
        cmd = 'docker volume prune --force || true'
        subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
    else:
        cmd = 'sudo podman network create --subnet 192.168.28.192/26 --ip-range 192.168.28.192/26 cicd-oai-public-net'
        print (cmd)
        netUpStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(netUpStatus.strip()).split('\n'):
            print(line)
        time.sleep(1)
        cwd = os.getcwd()
        cmd = 'sudo podman run --name cicd-oai-nef --network cicd-oai-public-net --ip 192.168.28.210'
        cmd += ' --env-file ./ci-scripts/podman/nef.env -d ' + tag
        print (cmd)
        contUpStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(contUpStatus.strip()).split('\n'):
            print(line)
        time.sleep(20)
        cmd = 'sudo podman inspect --format="STATUS: {{.State.Healthcheck.Status}}" cicd-oai-nef'
        print (cmd)
        healthStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(healthStatus.strip()).split('\n'):
            print(line)
            if re.search('STATUS:', line):
                if re.search('STATUS: healthy', line):
                    status = 0
                else:
                    status = -1
        cmd = 'sudo podman logs cicd-oai-nef'
        print (cmd)
        logStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(logStatus.strip()).split('\n'):
            print(line)
        cmd = 'sudo podman rm -f cicd-oai-nef'
        print (cmd)
        contDwnStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(contDwnStatus.strip()).split('\n'):
            print(line)
        cmd = 'sudo podman network rm cicd-oai-public-net'
        print (cmd)
        netDwnStatus = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        for line in str(netDwnStatus.strip()).split('\n'):
            print(line)
        cmd = 'sudo podman volume prune --force || true'
        subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
    return status

if __name__ == '__main__':
    main()
