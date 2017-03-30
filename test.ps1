$prevCD = pwd
cd x64/Release

$repetitions = 1e3

Write-Host "Starting nTnV"
./NoThreadsNoVectorization.exe $repetitions

Write-Host "Starting nTyV"
./NoThreadsYesVectorization.exe $repetitions

Write-Host "Starting yTnV"
./YesThreadsNoVectorization.exe $repetitions

Write-Host "Starting yTyV"
./YesThreadsYesVectorization.exe $repetitions

cd $prevCD