# libcurl-attacker

# Make sure libcurl-dev is installed, choose Openssl version!
sudo sudo apt  install libcurl-dev  
Reading package lists... Done  
Building dependency tree       
Reading state information... Done  
Package libcurl-dev is a virtual package provided by:  
  libcurl4-openssl-dev 7.68.0-1ubuntu2.6  
  libcurl4-nss-dev 7.68.0-1ubuntu2.6  
  libcurl4-gnutls-dev 7.68.0-1ubuntu2.6  
You should explicitly select one to install.  

# Compile command on linux
gcc libc_attacker.c.c -o libc_attacker -lcurl
