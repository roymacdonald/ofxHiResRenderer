# ofxHiResRenderer


Hi Resolution renderer for openFrameworks.


## Introduction

This addon provides a class that will let you render hi resolution images from what you see on screen. This is achieved by doing a [tiled render](https://en.wikipedia.org/wiki/Tiled_rendering).

## How to use:

You will need to declare an instance of `ofxHiResRenderer` somewhere in your code. It could be either a class variable or a temporary instance created when a specific event happens. It's up to you which one to choose.

There is only one public function in the `ofxHiResRenderer` class.
This is 
 
    void render(const ofCamera& cam, const ofRectangle& viewport, float scale, std::function<void()> drawScene, std::string path);

Its arguments are as follows:

* `const ofCamera& cam` Reference to the camera that you want to use.
* `const ofRectangle& viewport` Reference to the camera's viewport. If you are not using any you should pass `ofGetCurrentViewport()`.
* `float scale` The scale factor. This value must be more than one. It is how many times larger the render will be than what you can see on screen (actually it is how many times the size of the passed viewport). This will determine the final image size, which is `vieport.width * scale , viewport.height * scale`.
* `std::function<void()> drawScene` The function that draws the stuff into your screen. This can be an `std::function` instance, a lambda expression, or a regular class method binded using `std::bind` (as you can see in the example).
* `std::string path` this is the file path where to save the rendered image. This file needs an alpha channel, so avoid jpegs, otherwise you'll get a white background. The background color is not rendered. It is transparent.

## TO DO

* Render method that doesnt require a camera, so scenes that dont have cameras can be rendered.
* Option to save with or without background.
* Allow setting the rendered image size instead of the scale.


## License

Read `license.md`.

## Compatibility

Works with openframeworks version 0.10 onwards.

Actually any version after commit [908ccb3ef5b75cc868f5e5aea3212799b2473a84](https://github.com/openframeworks/openFrameworks/commit/908ccb3ef5b75cc868f5e5aea3212799b2473a84)

### Version 0.1 (09/27/2017):
first version.


