# CyberPlat CIPF usage example

Cyberplat libraries http://www.cyberplat.ru/download/api.zip

## Compiling

Just run `make` in repo directory.

## Usage

Signing message

    ./sign [message] [path to secret key] [secret key pass]
    
Verifying signed message

    ./verify [signed message] [path to CA key] [path to public key] [public key serial]

