$prevCD = pwd
cd x64/Release

Write-Host "Starting nTnV"
./NoThreadsNoVectorization.exe 10e5

Write-Host "Starting nTyV"
./NoThreadsYesVectorization.exe 10e5

Write-Host "Starting yTnV"
./YesThreadsNoVectorization.exe 10e5

Write-Host "Starting yTyV"
./YesThreadsYesVectorization.exe 10e5

cd $prevCD