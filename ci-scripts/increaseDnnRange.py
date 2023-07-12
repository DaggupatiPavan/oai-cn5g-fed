#!/usr/bin/env python3
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
------------------------------------------------------------------------------
For more information about the OpenAirInterface (OAI) Software Alliance:
  contact@openairinterface.org
---------------------------------------------------------------------
"""

import argparse
import logging
import os
import re
import sys

logging.basicConfig(
    level=logging.DEBUG,
    stream=sys.stdout,
    format="[%(asctime)s] %(levelname)8s: %(message)s"
)

def _parse_args() -> argparse.Namespace:
    """Parse the command line args

    Returns:
        argparse.Namespace: the created parser
    """
    example_text = '''example:
        ./ci-scripts/increaseDnnRange.py --help
        ./ci-scripts/increaseDnnRange.py docker-compose-file DC_FILENAME --nb-users NB_USERS_TO_ADD'''

    parser = argparse.ArgumentParser(description='OAI 5G CORE NETWORK Utility tool',
                                    epilog=example_text,
                                    formatter_class=argparse.RawDescriptionHelpFormatter)

    parser.add_argument(
        '--docker-compose-file', '-dcf',
        action='store',
        help='Docker-compose File to modify',
    )

    parser.add_argument(
        '--nb-users', '-n',
        action='store',
        type=int,
        default=30,
        help='Number of Users to add',
    )
    return parser.parse_args()

if __name__ == '__main__':
    # Parse the arguments
    args = _parse_args()

    cwd = os.getcwd()
    if not os.path.isfile(os.path.join(cwd, args.docker_compose_file)):
        logging.error(f'{args.docker_compose_file} does not exist')
        sys.exit(-1)

    startingIP = '12.1.0.2'
    endingIP = '12.1.0.50'
    cicdrSuffix = '24'
    if args.nb_users < 1023:
        endingIP = '12.1.3.254'
        cicdrSuffix = '22'
    elif args.nb_users < 2047:
        endingIP = '12.1.7.254'
        cicdrSuffix = '21'
    elif args.nb_users < 4095:
        endingIP = '12.1.15.254'
        cicdrSuffix = '20'
    elif args.nb_users < 8191:
        endingIP = '12.1.31.254'
        cicdrSuffix = '19'
    elif args.nb_users < 16383:
        endingIP = '12.1.63.254'
        cicdrSuffix = '18'

    lines = ''
    with open(os.path.join(cwd, args.docker_compose_file), 'r') as rfile:
        for line in rfile:
           if (re.search('DNN_RANGE0=12', line) is not None) or (re.search('DNN_RANGE1=12', line) is not None):
               lines += re.sub('12', '13', line)
           elif (re.search('DNN_RANGE2=12', line) is not None):
               lines += re.sub('12.1.1.2 - 12.1.1.50', f'{startingIP} - {endingIP}', line)
           elif (re.search('NETWORK_UE_IP=12.1.1.0/24', line) is not None):
               lines += re.sub('12.1.1.0/24', f'12.1.0.0/{cicdrSuffix}', line)
           elif (re.search('ip route add 12.1.1.0/24', line) is not None):
               lines += re.sub('12.1.1.0/24', f'12.1.0.0/{cicdrSuffix}', line)
           elif (re.search('grep 12.1.1', line) is not None):
               lines += re.sub('grep 12.1.1', 'grep 12.1.0', line)
           else:
               lines += line

    with open(os.path.join(cwd, args.docker_compose_file), 'w') as wfile:
        wfile.write(lines)

    sys.exit(0)
