param (
    [Alias("d", "dockerfile-loc")][string]$DOCKERFILE_LOC = $(Get-Location).ToString(),
    [Alias("v", "volume-loc")][string]$VOLUME_LOC = "C:\Users\$($env:UserName)"
)

# Build docker image if not already build
docker images -q moovie-desktop 2>&1 | Out-Null
if ( !$? )
{
    # Resolve full dockerfile location path
    $DOCKERFILE_LOC = $((Resolve-Path $DOCKERFILE_LOC).ToString())
    Write-Output "Using Dockerfile location '$DOCKERFILE_LOC'"

    Write-Output "Building docker image (This can take a while)"
    docker build -t moovie-desktop $DOCKERFILE_LOC | Out-Null
}

# Resolve full volume path
$VOLUME_LOC = $((Resolve-Path $VOLUME_LOC).ToString())
Write-Output "Including volume $VOLUME_LOC"

# Run docker image with moovie-desktop
Write-Output "Running docker image"
docker run `
    --user 1000 `
    --workdir /home/workspace `
    --volume ${VOLUME_LOC}:/home/workspace `
    --env DISPLAY=host.docker.internal:0.0 `
    moovie-desktop 2> Out-Null