# opengl-game-engine

This project is a simple game engine that I am building in order to learn the basics of OpenGL, Game Development, as well as Audio programming.

## Dependencies

I will probably try to rewrite some of the dependencies from scratch at some point, but for now these are the libraries i am using:
- `OpenGL`
- `glad`
- `assimp`
- `stb_image`

The code in this repository is heavily based on the materials provided by the website [learnopengl.com](https://learnopengl.com). It is a great resource and I highly recommend it.

## How to compile
In order to compile the project you will need to use `cmake`.

After compiling an example you will need to enter its directory before running it (ex. enter `/build/Examples/Pong/` and run `./pong-example`). This is because for now the program uses relative paths which rely on your working directory.