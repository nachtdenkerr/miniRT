# 🖼️ MiniRT

MiniRT is a minimal ray tracer written in C using the miniLibX graphics library.  
This project is part of the 42 curriculum and serves as an introduction to computer graphics, ray-object intersection, light physics, and rendering pipelines.

# 🎯 Project Goal

MiniRT demonstrates the core principles of ray tracing:  

Simulate how light rays interact with simple 3D objects (spheres, planes, cylinders)  
Render a static scene defined in a .rt file. 
Display the resulting image in a window. 
Learn how to implement math-heavy algorithms step by step — without external ray tracing engines. 
🗂️ Features

## ✅ Mandatory

Parse .rt scene description files<br/>
Support Ambient Light, Camera, Light Source<br/>
Render Spheres, Planes, Cylinders with:<br/>
Correct intersection calculation<br/>
Ambient and diffuse lighting<br/>
Hard shadows<br/>
Basic transformations: translation & rotation<br/>
Real-time display with MiniLibX<br/>
Clean exit on ESC key or window close<br/>

## ✨ Bonus (Optional)

Specular reflection (Phong)<br/>
Checkerboard pattern for planes<br/>
Additional objects (e.g., Cones)<br/>
Multi-spot lights<br/>
Bump mapping

# ⚙️ Usage

## Clone and build
```
git clone <repo_url>
cd miniRT
make
```

## Run with a scene file
./miniRT scenes/example.rt

## 📌 Scene Format Example
```
A 0.2 255,255,255       # Ambient light
C 0,0,0 0,0,1 70        # Camera
L 0,10,10 0.7 255,255,255  # Light

sp 0,0,20 10 255,0,0    # Sphere
pl 0,-10,0 0,1,0 0,255,0  # Plane
cy 30,0,20 0,0,1 5 15 0,0,255 # Cylinder
```
## ✅ Controls

ESC → Quit<br/>
Red cross → Quit

# 💡 Learning Outcomes

Understand ray-object math (intersection tests)<br/>
Practice linear algebra and vector operations<br/>
Work with a low-level graphics library<br/>
Design and parse file input robustly<br/>
Build a real rendering pipeline from scratch<br/>

Enjoy tracing rays and happy rendering! 🌟