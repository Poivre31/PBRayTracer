$base = Split-Path $PSScriptRoot -Parent
Set-Location $base

$subfolders = @("VegaEngine", "OptiqueOndulatoire", "OrionRayTracer", "SampleProject")
$extensions = ".cpp",".h",".comp",".frag",".vert",".ixx"

$total = 0

foreach ($sf in $subfolders) {
    $path = Join-Path $base $sf
    $count = (Get-ChildItem -Path $path -Recurse |
              Where-Object { $extensions -contains $_.Extension } |
              Get-Content).Count

    Write-Host "${sf}: $count lines"

    $total += $count
}

Write-Host "-----------------"
Write-Host "TOTAL: $total lines"
Read-Host -Prompt "exit"
