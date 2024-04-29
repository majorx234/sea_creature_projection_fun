# Info
- WIP, this codes is not useable
- create an animation software, to:
  - take self painted pictures of fishes, starfish and jellyfish
  - animate them in a swimming way
  - create a videostream for projection purpose

# Development Process
- code in small prototype steps
  - create an executable or a new lib for each main feature

## components:
### 1.digitalize images from cam
- read handcrafted pictures of fish and digitalie them to texture friendly image files
- niy
### 2.create images via touch
- alternative to cam image source
- niy
### 3.renderer and scene generation
- takes images of fishes and creates "deep water scene"

# Steps of development
## 1. main_textures_bouncing.cpp
- shows how to load texture and do animation in render loop
## 2. main_figures_bouncing.cpp
- shows how to organise elements in figures (objects)
## 3. main_render_pipeline.cpp
- build structure of pipeline to render objects
## 4. main_render_pipeline_moving_figures.cpp
- main loop is doing the complete pipeline processing and rendering of objects
  - movement
  - detection of out-of-screen
  - drawing on screen

# Todo
## 1.digitalize images from cam
- start simple implementation with background detection
  - maybe OpenCV based
## 2.create images via touch
- build simple paint program maybe QT based
  - simple drawing like QtDraw example
  - buttons for saving as image
## 3.renderer and scene generation
- add more movement types
- add animation for movements
- have config parser to generate scene out of that
- automatically check folder for new images and create figures out of them
