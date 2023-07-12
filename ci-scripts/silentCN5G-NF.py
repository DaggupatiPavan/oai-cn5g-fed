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
        ./ci-scripts/silentCN5G-NF.py --help
        ./ci-scripts/silentCN5G-NF.py --docker-compose-file DC_FILENAME --amf-log-level error
        ./ci-scripts/silentCN5G-NF.py --docker-compose-file DC_FILENAME --amf-silent'''

    parser = argparse.ArgumentParser(description='OAI 5G CORE NETWORK Utility tool',
                                    epilog=example_text,
                                    formatter_class=argparse.RawDescriptionHelpFormatter)

    parser.add_argument(
        '--docker-compose-file', '-dcf',
        action='store',
        help='Docker-compose File to modify',
    )

    # ALL NF arguments
    parser.add_argument(
        '--all-silent',
        action='store_true',
        default=False,
        help='Make all NFs silent',
    )

    parser.add_argument(
        '--all-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set all NFs to the same log level',
    )

    # AMF arguments
    parser.add_argument(
        '--amf-silent',
        action='store_true',
        default=False,
        help='Make AMF NF silent',
    )

    parser.add_argument(
        '--amf-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set AMF log level',
    )

    # SMF arguments
    parser.add_argument(
        '--smf-silent',
        action='store_true',
        default=False,
        help='Make SMF NF silent',
    )

    parser.add_argument(
        '--smf-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set SMF log level',
    )

    # NRF arguments
    parser.add_argument(
        '--nrf-silent',
        action='store_true',
        default=False,
        help='Make NRF NF silent',
    )

    parser.add_argument(
        '--nrf-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set NRF log level',
    )

    # SPGWU arguments
    parser.add_argument(
        '--spgwu-silent',
        action='store_true',
        default=False,
        help='Make SPGWU NF silent',
    )

    parser.add_argument(
        '--spgwu-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set SPGWU log level',
    )

    # AUSF arguments
    parser.add_argument(
        '--ausf-silent',
        action='store_true',
        default=False,
        help='Make AUSF NF silent',
    )

    parser.add_argument(
        '--ausf-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set AUSF log level',
    )

    # UDM arguments
    parser.add_argument(
        '--udm-silent',
        action='store_true',
        default=False,
        help='Make UDM NF silent',
    )

    parser.add_argument(
        '--udm-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set UDM log level',
    )

    # UDR arguments
    parser.add_argument(
        '--udr-silent',
        action='store_true',
        default=False,
        help='Make UDR NF silent',
    )

    parser.add_argument(
        '--udr-log-level',
        action='store',
        default='',
        choices = ["info", "error", "warning"],
        help='Set UDR log level',
    )

    return parser.parse_args()

if __name__ == '__main__':
    # Parse the arguments
    args = _parse_args()
    # Finalize arguments
    if args.amf_silent:
        args.amf_log_level = 'off'
    if args.smf_silent:
        args.smf_log_level = 'off'
    if args.nrf_silent:
        args.nrf_log_level = 'off'
    if args.spgwu_silent:
        args.spgwu_log_level = 'off'
    if args.ausf_silent:
        args.ausf_log_level = 'off'
    if args.udm_silent:
        args.udm_log_level = 'off'
    if args.udr_silent:
        args.udr_log_level = 'off'
    if args.all_silent:
        args.amf_log_level = 'off'
        args.smf_log_level = 'off'
        args.nrf_log_level = 'off'
        args.spgwu_log_level = 'off'
        args.ausf_log_level = 'off'
        args.udm_log_level = 'off'
        args.udr_log_level = 'off'
    if args.all_log_level != '':
        args.amf_log_level = args.all_log_level
        args.smf_log_level = args.all_log_level
        args.nrf_log_level = args.all_log_level
        args.spgwu_log_level = args.all_log_level
        args.ausf_log_level = args.all_log_level
        args.udm_log_level = args.all_log_level
        args.udr_log_level = args.all_log_level

    cwd = os.getcwd()
    if not os.path.isfile(os.path.join(cwd, args.docker_compose_file)):
        logging.error(f'{args.docker_compose_file} does not exist')
        sys.exit(-1)

    lines = ''
    amfContainerFound = False
    smfContainerFound = False
    nrfContainerFound = False
    spgwuContainerFound = False
    ausfContainerFound = False
    udmContainerFound = False
    udrContainerFound = False
    with open(os.path.join(cwd, args.docker_compose_file), 'r') as rfile:
        for line in rfile:
           lines += line
           # amf
           if re.search('image: oaisoftwarealliance/oai-amf:', line) is not None and args.amf_log_level != '':
               amfContainerFound = True
           if re.search('TZ=Europe', line) is not None and amfContainerFound and args.amf_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.amf_log_level}', line)
               lines += newLine
               amfContainerFound = False
           # smf
           if re.search('image: oaisoftwarealliance/oai-smf:', line) is not None and args.smf_log_level != '':
               smfContainerFound = True
           if re.search('TZ=Europe', line) is not None and smfContainerFound and args.smf_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.smf_log_level}', line)
               lines += newLine
               smfContainerFound = False
           # nrf
           if re.search('image: oaisoftwarealliance/oai-nrf:', line) is not None and args.nrf_log_level != '':
               nrfContainerFound = True
           if re.search('TZ=Europe', line) is not None and nrfContainerFound and args.nrf_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.nrf_log_level}', line)
               lines += newLine
               nrfContainerFound = False
           # spgwu
           if re.search('image: oaisoftwarealliance/oai-spgwu-tiny:', line) is not None and args.spgwu_log_level != '':
               spgwuContainerFound = True
           if re.search('TZ=Europe', line) is not None and spgwuContainerFound and args.spgwu_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.spgwu_log_level}', line)
               lines += newLine
               spgwuContainerFound = False
           # ausf
           if re.search('image: oaisoftwarealliance/oai-ausf:', line) is not None and args.ausf_log_level != '':
               ausfContainerFound = True
           if re.search('TZ=Europe', line) is not None and ausfContainerFound and args.ausf_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.ausf_log_level}', line)
               lines += newLine
               ausfContainerFound = False
           # udm
           if re.search('image: oaisoftwarealliance/oai-udm:', line) is not None and args.udm_log_level != '':
               udmContainerFound = True
           if re.search('TZ=Europe', line) is not None and udmContainerFound and args.udm_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.udm_log_level}', line)
               lines += newLine
               udmContainerFound = False
           # udr
           if re.search('image: oaisoftwarealliance/oai-udr:', line) is not None and args.udr_log_level != '':
               udrContainerFound = True
           if re.search('TZ=Europe', line) is not None and udrContainerFound and args.udr_log_level != '':
               newLine = re.sub('TZ=Europe.*$', f'LOG_LEVEL={args.udr_log_level}', line)
               lines += newLine
               udrContainerFound = False

    with open(os.path.join(cwd, args.docker_compose_file), 'w') as wfile:
        wfile.write(lines)

    sys.exit(0)
