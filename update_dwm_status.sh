#!/bin/bash
declare -r color_normal=""
declare -r color_selected=""
declare -r color_warning=""
declare -r color_error=""
#color_statuscolors=""
declare -r color_ok=""
declare -r color_yellow=""

#Time and Date
declare -r logo_date_clock=""
declare -r Date=$color_selected$logo_date_clock$color_normal$(date +"%a, %d.%m %R")

#Audio
# TODO currently only works with ALSA, not with pulseaudio
volume() {
  local logo_volume_high=""
  local logo_volume_low=""
  local logo_volume_mute=""
  local Vol_raw=$(awk '/dB/' <(amixer get Master))
  local Volume_percentage=$(awk '/dB/ { gsub(/[\[\]]/,""); print $4}' <(amixer get Master)| sed -e 's/%//g')
  if [ "$(echo $Vol_raw | awk '/dB/ { gsub(/[\[\]]/,""); print $6}')" == "on" ]
  then
    if [ $Volume_percentage -ge 60 ]
    then
      Volume=$color_selected$logo_volume_high #ganze kraft
    else
      Volume=$color_selected$logo_volume_low #weniger
    fi
  else
    Volume=$color_warning$logo_volume_mute #mute symbol
  fi
  Volume+=$color_normal$Volume_percentage" "
  echo $Volume
}

#Batterie
battery() {
  declare -r logo_bat=""
  declare -r logo_bat_plug=""
  declare -r ogo_bat_full=""
  declare -r ogo_bat_medium=""
  declare -r logo_bat_low=""
  declare -r logo_bat_emty=""
  if [ -f /usr/bin/acpi ]
  then
    Bat=$(acpi -b)
    if [ "$Bat" != "" ]
    then #Bat="B "$(awk 'sub(/,/,"") {print $3, "["$4"]"}' <(acpi -b) | sed -e 's/,//g')" | "
      Bat_percentage=$(echo $Bat | awk 'sub(/,/,"") {print $4}' | sed -e 's/,//g' -e 's/%//g')
      if [[ $Bat_percentage -ge 90 ]]
      then #bis 90% -> das volle logo
        Bat_logo=$color_ok$logo_bat_full$color_normal
      else
        if [[ $Bat_percentage -ge 70 ]]
        then #bis 70% -> das fast volle logo
          Bat_logo=$color_yellow$logo_bat_medium$color_normal
        else
          if [[ $Bat_percentage -ge 40 ]]
          then #bis 40% -> das fast leere logo
            Bat_logo=$color_warning$logo_bat_low$color_normal
          else #unter 40% -> das leere logo
            Bat_logo=$color_error$logo_bat_emty$color_normal
          fi
        fi
      fi
      Bat_status=$(echo $Bat | awk 'sub(/,/,"") {print $3}' | sed -e 's/,//g')
      if [ "$Bat_status" == "Charging" ]
      then
        Bat_status=$color_ok$logo_bat_plug$color_normal
      else
        if [ "$Bat_status" == "Full" ] #show plug if battery is fully charged and ac on
        then
          Bat_logo=$color_ok$logo_bat_plug$color_normal
        fi
        Bat_status="" #don't display text message
      fi
      Bat_time=$(echo $Bat | awk 'sub(/,/,"") {print $5}' | sed -e 's/,//g')
      if [ "$Bat_time" == "discharging" ] || [ "$Bat_time" == "charging" ]
      then
        Bat_time=""
      else
        Bat_time=$(echo $Bat_time | awk -F: '{print $1":"$2}')
        if [ "$Bat_time" == ":" ]
        then
          Bat_time=""
        fi
      fi
      Bat_stat=$color_selected$logo_bat$color_normal$Bat_status$Bat_time$Bat_logo" "
    fi
  fi
  echo $Bat_stat
}

#Ram (benutzte Prozente = gesammt($2)-(frei+cache($4+$7))/gesammt)
#Mem=$color_selected""$color_normal" "$(($(free -m|awk '/^Mem:/{print $2-($4+$7)}')*100/$(free -m|awk '/^Mem:/{print $2}')))"  "

#Cpu
#Cpu=$color_selected""$color_normal" "$(top -bn 1 | grep '%Cpu' | awk '{print $2'})"  "

#network
declare -r logo_net=""
declare -r logo_net_lan=""
declare -r logo_net_wlan=""
declare -r logo_net_wlan_high=""
declare -r logo_net_wlan_medium=""
declare -r logo_net_wlan_low=""
network() {
  if [ -f /sys/class/net/wlan0/address ] #wlan0 present? check for mac address
  then
    Ip=$(ifconfig wlan0 | head -n 2 | sed -e 's/inet//g' | awk '{print $1}' | grep -v wlan0:)
    #ifconfig is deprecated FIXME
    if [ "$Ip" != "ether" ] #wlan up
    then
      Ssid=$(iwconfig wlan0 | head -n 1 | sed -e 's/ESSID://g' | sed -e 's/\"//g' | awk '{for (i = 4; i <= NF; i++) printf $i " "; print ""}')
      if [ "$Ssid" == "off/any" ] #wlan is currently dissconnecting
      then
        Ip=""
      else
        if [ "$Ip" == "6" ]
        then
          Ip=$color_normal"connecting ..."
          Ssid=$Ip" "$Ssid #since i removed ip from displaying
        fi
        Net_quality=$(iwconfig wlan0 | awk '{print $2}' | grep Quality | sed -e 's/Quality=//g' | tr "/" " ")
        Net_percentage=$(echo $Net_quality | awk '{print ($1*100/$2)}' | tr "." " " | awk '{print $1}')
        if [ $Net_percentage -ge 60 ] #Net_percentage > 60%
        then
          Net_percentage_icon=$color_ok$logo_net_wlan_high #"" 3 bars
        else
          if [ $Net_percentage -ge 40 ]
          then
            Net_percentage_icon=$color_yellow$logo_net_wlan_medium #"" 2 bars
          else
            Net_percentage_icon=$color_error$logo_net_wlan_low #"" 1 bar remaining
          fi
        fi
        Net=$color_normal$Ssid$Net_percentage_icon    #$Ip" "$Ssid
      fi
    fi
  fi
  if [ "$Ip" == "ether" ] || [ "$Ip" == "" ] #wlan0 not present or has no ip address assigned
  then
    Ip=$(ifconfig eth0 | head -n 2 | sed -e 's/inet//g' | awk '{print $1}' | grep -v eth0:)
    if [ "$Ip" == "ether" ] || [ "$Ip" == "" ] #eth down
    then
      if [ -f /sys/class/net/wlan0/address ] #check if wlan0 is present
      then
        if [ "$(iwconfig wlan0 | grep Tx-Power | sed -e 's/=/ /g' | awk '{print $6}')" == "off" ] #wlan turned off
        then
          Net=$color_error"off "$logo_net_wlan
        else
          Net=$color_warning"down "$logo_net_wlan
        fi
      else
        Net=$color_error"down "$logo_net_lan
      fi
    else #eth0 up
      if [ "$Ip" == "6" ]
      then
        Ip=$color_normal"connecting ... "
        Net=$Ip$logo_net_lan #show that eth0 is connecting
      else
        Net=$color_normal$Ip$color_ok$logo_net_lan
      fi
    fi
  fi
  echo $color_selected$logo_net$Net" "
}


####################
# daemons / services
####################

# check if cups is running
daemon_cups(){
  if [ -d /var/run/cups/ ]
  then
    echo $color_ok"CUPS"
  else
    echo $color_error"CUPS"
  fi
}

# check if dropbox is running
daemon_dropbox() {
  local Dropbox_pid=$(pidof dropbox)
  if [ "$Dropbox_pid" != "" ]
  then
    echo $color_ok"Dropbox"
  else
    echo $color_error"Dropbox"
  fi
}

# check if apache is running
daemon_http() {
  if [ -d /var/run/httpd/ ]
  then
    if [ -f /var/run/httpd/httpd.pid ]
    then
      echo $color_ok"HTTP"
    else
      echo $color_error"HTTP"
    fi
  else
    echo $color_error"HTTP"
  fi
}

# check if mysql is running
daemon_mysql() {
  if [ -d /var/run/mysqld/ ]
  then
    if [ -f /var/run/mysqld/mysqld.pid ]
    then
      echo $color_ok"MySql"
    else
      echo $color_error"MySql"
    fi
  else
    echo $color_error"MySql"
  fi
}

# check if ssh daemon is running
daemon_ssh() {
  if [ -f /var/run/sshd.pid ]
  then
    echo $color_ok"SSH"
  else
    echo $color_error"SSH"
  fi
}

#coretemp
declare -r logo_temp=""
coretemp() {
  Temp_data0=$(sensors | grep Core\ 0 | awk '{print $3}' | sed -e 's/+//g' -e 's/\.0//g')
  if [ "$Temp_data0" != "" ]
  then
    Temp_data0+=" "
  fi
  Temp_data1=$(sensors | grep Core\ 1 | awk '{print $3}' | sed -e 's/+//g' -e 's/\.0//g')
  if [ "$Temp_data1" != "" ]
  then
    Temp_data1+=" "
  fi
  Temp_data2=$(sensors | grep Core\ 2 | awk '{print $3}' | sed -e 's/+//g' -e 's/\.0//g')
  if [ "$Temp_data2" != "" ]
  then
    Temp_data2+=" "
  fi
  Temp_data3=$(sensors | grep Core\ 3 | awk '{print $3}' | sed -e 's/+//g' -e 's/\.0//g')
  echo $color_selected$logo_temp$color_normal$Temp_data0$Temp_data1$Temp_data2$Temp_data3" "
}


# daemonlogos
#trident: 
declare -r logo_deamon=""
daemons() {
  echo $color_selected$logo_deamon$(daemon_cups)$(daemon_dropbox)$(daemon_http)$(daemon_mysql)$(daemon_ssh)" "
}

if [ -f /sys/class/backlight/acpi_video0/brightness ] #am laptop
then
  logo_display=""
  #display=$(xbacklight | awk 'split ($1,a,".");$6=a[1]' | awk '{print $2}' | grep -v "^$")
  display=$(cat /sys/class/backlight/acpi_video0/brightness | awk '{print ($1/.15)}' | tr "." " " | awk '{print $1}')
  Display=$color_selected$logo_display$color_normal$display"  "
fi

#Zusammenfassung
Output=$(daemons)$(network)$Cpu$(coretemp)$Mem$(battery)$(volume)$Display$Date
if [ "$1" != "" ]
then #mit Parameter gestarted (debug)
  echo $Output
else #ohne parameter gestarted
  xsetroot -name "$Output"
fi
sleep 1
