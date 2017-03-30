$prevCD = pwd
cd x64/Release

$size = 3e4

Write-Host "Starting nTnV"
./NoThreadsNoVectorization.exe $size

Write-Host "Starting nTyV"
./NoThreadsYesVectorization.exe $size

Write-Host "Starting yTnV"
./YesThreadsNoVectorization.exe $size

Write-Host "Starting yTyV"
./YesThreadsYesVectorization.exe $size

cd $prevCD