
stty -F /dev/ttyUSB1 38400 -echo -echoe -echok
stty -F /dev/ttyUSB0 4800 -echo -echoe -echok
fname=log_`date +%Y%m%d%H%M`.txt
cat /dev/ttyUSB1 | tee -a $fname &
cat /dev/ttyUSB0 | tee -a $fname &
