# # Display text
# Write-Host "Hello, PowerShell!"

# # Store and use a variable
# $name = "World"
# Write-Output "Hello, $name"

# # Get help
# Get-Help Get-Process

# # List files and folders
# Get-ChildItem

# # Change directory
# Set-Location .\Documents

# # Create a folder and file
# New-Item -ItemType Directory -Path .\Example
# New-Item -ItemType File -Path .\Example\notes.txt

# # Read and write text
# Set-Content -Path .\Example\notes.txt -Value "Sample text"
# Get-Content .\Example\notes.txt

# # Conditional statement
# if ($name -eq "World") {
# 	Write-Host "Match found"
# } else {
# 	Write-Host "No match"
# }

# # Loop
# foreach ($item in 1..3) {
# 	Write-Host $item
# }

# # Run a command and stop on errors
# Get-Process -ErrorAction Stop

#My Testing
#1
$name = "Musa"
$count = 67
Write-Host "Assalam O Alaikum $name ! , Your Fav Number is $count"

#2
Get-Process | Where-Object {$_.CPU -gt 10} | Sort-Object CPU -Descending | Select-Object -First 5

Get-ChildItem -Path . -Recurse -Filter *.cs

#3
if($count -gt 3){
    Write-Host "BIG NUMBER"
}
else{
    Write-Host "SMALL NUMBER"
}

#4
function Get-MyInfo {
    param (
        [string]$UserName,
        [int]$Age
    )
    Write-Host "User Name: $UserName"
    Write-Host "Age: $Age"
}

function Get-FileCount{
    param (
        [string]$Path, [string]$Extension = "*.*"
    )
    (Get-ChildItem -Path $Path -Filter $Extension -Recurse).Count
    
}

Get-FileCount -Path . -Extension *.cs


#5
$content = Get-Content -Path "log.txt" -ErrorAction SilentlyContinue

"log entry" | Out-File -Append -FilePath "log.txt"

try{
    Get-Content "missing.txt" -ErrorAction Stop
} catch{    
    Write-Host "File not found"
}

#6
& cmd.exe /c "exit 1"
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed" }
