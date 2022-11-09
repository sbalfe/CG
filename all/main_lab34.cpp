/****************************************************************************
 *
 * krt - Ken's Raytracer - Coursework Edition. (C) Copyright 1993-2022.
 *
 * I've put a lot of time and effort into this code. For the last decade
 * it's been used to introduce hundreds of students at multiple universities
 * to raytracing. It forms the basis of your coursework but you are free
 * to continue using/developing forever more. However, I ask that you don't
 * share the code or your derivitive versions publicly. In order to continue
 * to be used for coursework and in particular assessment it's important that
 * versions containing solutions are not searchable on the web or easy to
 * download.
 *
 * If you want to show off your programming ability, instead of releasing
 * the code, consider generating an incredible image and explaining how you
 * produced it.
 */

/* This is the top level for the program you need to create for lab three and four.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// these are core raytracing classes
#include "framebuffer.h"
#include "scene.h"

// classes that contain our objects to be rendered, all derived from Object
#include "polymesh_object.h"
#include "sphere_object.h"
#include "plane_object.h"

// classes that contain our lights, all derived from Light
#include "directional_light.h"

// classes that contain the materials applied to an object, all derived from Material
#include "phong_material.h"
#include "falsecolour_material.h"

//classes that contain cameras, all derived from Camera
#include "simple_camera.h"
#include "full_camera.h"

using namespace std;

// you will find it useful during development/debugging to create multiple functions that fill out the scene.
void build_scene(Scene& scene)
{
	// The following transform allows 4D homogeneous coordinates to be transformed.It moves the supplied teapot model to somewhere visible.
    auto * transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, -2.7f,
			0.0f, 1.0f, 0.0f, 5.0f,
			0.0f, 0.0f, 0.0f, 1.0f);


	//  Read in the teapot model.
    auto* pm = new PolyMesh("../assets/teapot_smaller.ply", false);
    auto* plane = new PolyMesh("../assets/plane.ply",false);
	pm->apply_transform(*transform);
    pm->GenFaceNormals();
    pm->GenVertexNormals();

    auto* sphere = new Sphere(Vertex(-1.0f, 1.0f, 3.0f), 0.4f);
    auto* sphere2 = new Sphere(Vertex(1.5f, 0.0f, 1.5f), 0.4f);
    auto* sphere3 = new Sphere(Vertex(0.0f, 1.0f, 1.5f), 0.4f);


    auto* dl = new DirectionalLight(Vector(1.0f, -1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 0.0f));
	scene.add_light(dl);

	auto* bp1 = new Phong(Colour(0.2f, 0.0f, 0.0f), Colour(0.4f, 0.0f, 0.0f), Colour(0.4f, 0.4f, 0.4f), 40.f);
    auto* bp2_blue = new Phong(Colour(0.0f, 0.0f, 0.2f), Colour(0.0f, 0.0f, 0.4f), Colour(0.4f, 0.4f, 0.4f), 40.f);
    auto* bp2_grey = new Phong(Colour(0.5f, 0.5f, 0.5f), Colour(0.5f, 0.5f, 0.5f), Colour(0.4f, 0.4f, 0.4f), 40.f);
    auto* bp2 = new Phong(Colour(0.01f, 0.01f, 0.01f), Colour(0.0f, 0.0f, 0.0f), Colour(0.5f, 0.5f, 0.5f), 40.f);

    //pm->set_material(bp1);
	//scene.add_object(pm);

    //plane->set_material(bp1);
    //scene.add_object(plane);


	sphere->set_material(bp1);
    // sphere2->set_material(bp2_blue);
    // sphere3->set_material(bp2_blue);

	scene.add_object(sphere);
    //scene.add_object(sphere2);
    //scene.add_object(sphere3);
    pm->set_material(bp1);
    scene.add_object(pm);


}

// This is the entry point function to the program.
int main(int argc, char *argv[])
{
	int width = 512;
	int height = 512;
	// Create a framebuffer
    auto* fb = new FrameBuffer(width, height);
	
	// Create a scene
	Scene scene;
	
	// Setup the scene
	build_scene(scene);

	// Declare a camera
	// Camera *camera = new SimpleCamera(0.5f);

    // fov, position, look at, up.
	Camera* camera = new FullCamera(0.5f, Vertex(0.0f, 0.0f,-1.0f), Vector(0.0f, 0.0f,3.0f), Vector(0.0f, -1.0f, 0.0f));

	// Camera generates rays for each pixel in the framebuffer and records colour + depth.
	camera->render(scene,*fb);

	// Output the framebuffer colour and depth as two images
	fb->writeRGBFile((char *)"test.ppm");
	fb->writeDepthFile((char *)"depth.ppm");
	
	cerr << "\nDone.\n" << flush;
	
	// a debug check to make sure we don't leak hits.
	cerr << "Hit Pool " << Hit::pool_size << " Allocated " << Hit::allocated << "\n" << flush;
	return 0;
}
