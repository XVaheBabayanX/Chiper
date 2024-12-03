@echo off
setlocal enabledelayedexpansion

set scriptDir=%~dp0

set encryptedDir=!scriptDir!Encrypted
set decryptedDir=!scriptDir!Decrypted
set inputDir=!scriptDir!Input

if not exist "!encryptedDir!" mkdir "!encryptedDir!"
if not exist "!decryptedDir!" mkdir "!decryptedDir!"
if not exist "!inputDir!" mkdir "!inputDir!"

:menu
cls
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Get IP Address
echo 2. Make Traceroute
echo 3. Resolve DNS Name
echo 4. Encrypt Text 
echo 5. Decrypt Text
echo 6. Encrypt File 
echo 7. Decrypt File
echo 8. Compress File 
echo 9. Decompress File
echo 10. Calculate Hash Value (Text/File)
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="0" goto exit
goto menu

:get_ip
ipconfig | findstr "IPv4" 
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
set /p target="Enter the hostname or IP address: "
tracert %target%
pause
goto menu

:resolve_dns
set /p dns_name="Enter the DNS name: "
nslookup %dns_name%
pause
goto menu

:encrypt_text
cls
echo ===================================
echo     Choose Encryption Algorithm
echo ===================================
echo 1. Caesar
echo 2. Polybius
echo 3. Simple Substitution
echo 4. Transposition
echo 5. Vigenere
echo ===================================
set /p algorithm_choice="Enter the number corresponding to your choice: "

if "%algorithm_choice%"=="1" set algorithm=caesar
if "%algorithm_choice%"=="2" set algorithm=polybius
if "%algorithm_choice%"=="3" set algorithm=simple
if "%algorithm_choice%"=="4" set algorithm=transposition
if "%algorithm_choice%"=="5" set algorithm=vigenere

if not defined algorithm (
    echo Invalid choice. Please select a valid option.
    pause
    goto encrypt_text
)

set mode=encrypt
"D:\Visual Studio\С++\ProgSystemDefending\Chiper\x64\Debug\Chiper.exe" %mode% %algorithm% text text
pause
goto menu

:decrypt_text
cls
echo ===================================
echo     Choose Decryption Algorithm
echo ===================================
echo 1. Caesar
echo 2. Polybius
echo 3. Simple Substitution
echo 4. Transposition
echo 5. Vigenere
echo ===================================
set /p algorithm_choice="Enter the number corresponding to your choice: "

if "%algorithm_choice%"=="1" set algorithm=caesar
if "%algorithm_choice%"=="2" set algorithm=polybius
if "%algorithm_choice%"=="3" set algorithm=simple
if "%algorithm_choice%"=="4" set algorithm=transposition
if "%algorithm_choice%"=="5" set algorithm=vigenere

if not defined algorithm (
    echo Invalid choice. Please select a valid option.
    pause
    goto decrypt_text
)

set mode=decrypt
"D:\Visual Studio\С++\ProgSystemDefending\Chiper\x64\Debug\Chiper.exe" %mode% %algorithm% text text
pause
goto menu

:encrypt_file
cls
echo ===================================
echo     Choose Encryption Algorithm
echo ===================================
echo 1. Caesar
echo 2. Polybius
echo 3. Simple Substitution
echo 4. Transposition
echo 5. Vigenere
echo ===================================
set /p algorithm_choice="Enter the number corresponding to your choice: "

if "%algorithm_choice%"=="1" set algorithm=caesar
if "%algorithm_choice%"=="2" set algorithm=polybius
if "%algorithm_choice%"=="3" set algorithm=simple
if "%algorithm_choice%"=="4" set algorithm=transposition
if "%algorithm_choice%"=="5" set algorithm=vigenere

if not defined algorithm (
    echo Invalid choice. Please select a valid option.
    pause
    goto encrypt_file
)

set mode=encrypt

echo ===================================
echo     Enter File Name to Encrypt
echo ===================================
set /p filename="Enter the file name: "

set inputFile=!inputDir!\!filename!
set outputFile=!encryptedDir!\Encrypted!filename!

echo Encrypting file: !inputFile!
echo Encrypted file will be saved as: !outputFile!

"D:\Visual Studio\С++\ProgSystemDefending\Chiper\x64\Debug\Chiper.exe" %mode% %algorithm% "!inputFile!" "!outputFile!"
pause
goto menu

:decrypt_file
cls
echo ===================================
echo     Choose Decryption Algorithm
echo ===================================
echo 1. Caesar
echo 2. Polybius
echo 3. Simple Substitution
echo 4. Transposition
echo 5. Vigenere
echo ===================================
set /p algorithm_choice="Enter the number corresponding to your choice: "

if "%algorithm_choice%"=="1" set algorithm=caesar
if "%algorithm_choice%"=="2" set algorithm=polybius
if "%algorithm_choice%"=="3" set algorithm=simple
if "%algorithm_choice%"=="4" set algorithm=transposition
if "%algorithm_choice%"=="5" set algorithm=vigenere

if not defined algorithm (
    echo Invalid choice. Please select a valid option.
    pause
    goto decrypt_file
)

set mode=decrypt

echo ===================================
echo     Enter File Name to Decrypt
echo ===================================
set /p filename="Enter the file name: "

set inputFile=!encryptedDir!\!filename!
set outputFile=!decryptedDir!\Decrypted!filename!

echo Decrypting file: !inputFile!
echo Decrypted file will be saved as: !outputFile!

"D:\Visual Studio\С++\ProgSystemDefending\Chiper\x64\Debug\Chiper.exe" %mode% %algorithm% "!inputFile!" "!outputFile!"
pause
goto menu

:compress_file
set /p file="Enter the file path to compress: "
echo LZ77 compression requires external tools or scripts.
pause
goto menu

:decompress_file
set /p file="Enter the file path to decompress: "
echo LZ77 decompression requires external tools or scripts.
pause
goto menu

:hash_value
set /p input="!!!!! Enter text or file path: "
echo Default Hashing. Result in def-hash-%input% file
certutil -hashfile %input% > def-hash-%input%
echo Calculate Hash Value with MD5. Result in MD5-%input% file 
certutil -hashfile %input% MD5 > MD5%input%
echo Calculate Hash Value with SHA256. Result in SHA256-%input% file 
certutil -hashfile %input% SHA256 > SHA256-%input%
pause
goto menu

:exit
echo Exiting... Goodbye!

::exit
