#Before running EVK, you should change python files included in nrc_pkg as executable.
#Just do like below.

cd /home/pi/nrc_pkg
chmod -R 755 *

#Please refer the README file under ~/nrc_pkg for more information

#apply single-band (Sub1G) to EVK
./update.sh

#apply dual-band (Sub1G + 2.4GHz) to EVK
./update.sh dual
