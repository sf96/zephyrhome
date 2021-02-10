zephyrhome
===================

Projekt wykonano na Ubuntu_20_04_1

#  Inteligentny budynek w oparciu o system operacyjny Zephyr  

## Zadania, które wykonuje aplikacja:  
1. Informowanie użytkownika o swoim statusie przez port UART.  
2. Uruchamianie alarm po wykryciu pożaru przez czujnik dymu(należy obsłużyć przerwanie).  
3. Sterowanie natężeniem oświetlenia w zależności od natężenia światła na zewnątrz budynku.  
4. Sterowanie roletami w zależności od natężenia światła na zewnątrz budynku.  
5. Włączanie/wyłączanie systemu przyciskiem, w trakcie wyłączenia podtrzymywane są ustawienia systemu - natężenie oświetlenia i poziom rolet.  

## Przygotowanie środowiska pod projekt:  
### Renode:  

```
cd ~
wget https://github.com/renode/renode/releases/download/v1.11.0/renode-1.11.0.linux-portable.tar.gz

mkdir renode_portable
tar xf  renode-*.linux-portable.tar.gz -C renode_portable --strip-components=1

cd renode_portable
echo 'export PATH=~/renode_portable:"$PATH"' >> ~/.bashrc
source ~/.bashrc

cd ~
sudo apt install gnupg ca-certificates
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb https://download.mono-project.com/repo/ubuntu stable-focal main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
sudo apt update

sudo apt install mono-complete

sudo apt-get install policykit-1 libgtk2.0-0 screen uml-utilities gtk-sharp2 libc6-dev gcc python3 python3-pip libzmq5
```

### Zephyr:

```
sudo apt update
sudo apt upgrade

sudo apt install --no-install-recommends git cmake ninja-build gperf \
ccache dfu-util device-tree-compiler wget \
python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
make gcc gcc-multilib g++-multilib libsdl2-dev

cmake --version
// powinna byc 3.13.1 lub wyższa

pip3 install --user -U west
echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
source ~/.bashrc

west init ~/zephyrproject
cd ~/zephyrproject
west update
west zephyr-export
pip3 install --user -r ~/zephyrproject/zephyr/scripts/requirements.txt

cd ~
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.11.4/zephyr-sdk-0.11.4-setup.run
chmod +x zephyr-sdk-0.11.4-setup.run
./zephyr-sdk-0.11.4-setup.run -- -d ~/zephyr-sdk-0.11.4
```
