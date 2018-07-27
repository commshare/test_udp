#!/bin/bash

cp -f ./Godeps.json.template ./Godeps.json
cd ..
rm -rf ./vendor
docker run --rm -e GOPATH=/go/:/temp/ -v /d/temp/:/temp/ -v "$PWD":/go/src/myapp -w /go/src/myapp fananchong/godep save ./...

