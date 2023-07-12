# prompt has been removed for easier Ctrl+C Ctrl+V
# please update the following information according to your configuration

INSTANCE=1
PREFIX='/usr/local/etc/oai'
sudo mkdir -m 0777 -p $PREFIX
cp ../../etc/nef.conf  $PREFIX

declare -A NEF_CONF

NEF_CONF[@INSTANCE@]=$INSTANCE
NEF_CONF[@PREFIX@]=$PREFIX
NEF_CONF[@PID_DIRECTORY@]='/var/run'

NEF_CONF[@NEF_INTERFACE_NAME_FOR_SBI@]='wlo1'

NEF_CONF[@NEF_INTERFACE_PORT_FOR_SBI@]='80'
NEF_CONF[@NEF_INTERFACE_HTTP2_PORT_FOR_SBI@]='9090'
NEF_CONF[@NEF_API_VERSION@]='v1'

NEF_CONF[@AMF_IPV4_ADDRESS@]='127.0.0.1'
NEF_CONF[@AMF_PORT@]='80'
NEF_CONF[@AMF_HTTP2_PORT@]='9090'
NEF_CONF[@AMF_API_VERSION@]='v1'
NEF_CONF[@AMF_FQDN@]='oai_amf'

NEF_CONF[@SMF_IPV4_ADDRESS@]='127.0.0.1'
NEF_CONF[@SMF_PORT@]='80'
NEF_CONF[@SMF_HTTP2_PORT@]='9090'
NEF_CONF[@SMF_API_VERSION@]='v1'
NEF_CONF[@SMF_FQDN@]='oai_smf'

NEF_CONF[@UDM_IPV4_ADDRESS@]='127.0.0.1'
NEF_CONF[@UDM_PORT@]='80'
NEF_CONF[@UDM_HTTP2_PORT@]='9090'
NEF_CONF[@UDM_API_VERSION@]='v1'
NEF_CONF[@UDM_FQDN@]='oai_udm'


NEF_CONF[@USE_FQDN_DNS@]='no'
NEF_CONF[@USE_HTTP2@]='no'


for K in "${!NEF_CONF[@]}"; do 
  egrep -lRZ "$K" $PREFIX | xargs -0 -l sed -i -e "s|$K|${NEF_CONF[$K]}|g"
  ret=$?;[[ ret -ne 0 ]] && echo "Tried to replace $K with ${NEF_CONF[$K]}"
done
