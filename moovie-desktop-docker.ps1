param (
    [string]$DOCKERFILE_LOC = $(Get-Location).ToString()
)

# Build docker image if not already build
docker images -q moovie-desktop 2>&1 | Out-Null
if ( !$? )
{
    Write-Output "Using docker file location '$DOCKERFILE_LOC'"

    Write-Output "Building docker image (This can take a while)"
    docker build -t moovie-desktop $DOCKERFILE_LOC | Out-Null
}

# Run docker image with moovie-desktop
Write-Output "Run docker image"
docker run `
    --user 1000 `
    --workdir $("//c" + $(Get-Location).ToString().TrimStart("C:").Replace('\', '/')) `
    --volume /home/$USER/://c/home/$USER `
    --env DISPLAY=host.docker.internal:0 `
    moovie-desktop 2> Out-Null