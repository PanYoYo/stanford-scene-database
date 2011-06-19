
---- Stanford Scene Database

This project provides a barebones interface that demonstrates how to parse scene and model files in our scene database.
Our focus is on interior scenes, and our database does not contain outdoor environments.
Most scenes are rooms one might expect to find in a house or office building.

Although we experimented with using scenes directly from Google 3D Warehouse, we concluded it was not fruitful to pursue this because the segmentation quality, tagging quality, and model density of scenes on Google Warehouse are extremely poor.
Instead we build a model database using Google 3D Warehouse and have users model new scenes using our own interior modeling program, which we call SceneStudio:
http://graphics.stanford.edu/projects/SceneStudio/
If you are using Windows, feel free to model new scenes for us and upload them to the database.

This collection of scenes is useful for understanding the relationships between objects and related avenues of research that focus on understanding a collection of objects as a whole in addition to properties of isolated objects.
We converted the model database and scene description files into easily parsed ASCII formats in an attempt to make it easy for other researchers to use our database in their own work.

**** 1. Database Construction

Below is a list of steps describing the process we used to build our model and scene database.

1. Construct an approximate list of tags commonly found in interior environments.
2. Use Google 3D Warehouse's search engine to acquire SketchUp files for the first 20 pages of results for each tag.
3. Acquire a name and set of tags for each models from its HTML page.
4. Go through each SketchUp model, and manually select all the "isolated objects".
5. Use SketchUp to convert all the selected models to COLLADA (we then further convert them into Wavefront .obj files and a binary format used by SceneStudio).
6. Have multiple users use this model database to create interior scenes using SceneStudio, recording all their search queries.
7. Use these search queries to construct a new list of tags, and repeat steps 2-6 several times, until we have most of the relevant models on Google 3D Warehouse.

Here "isolated object" is used to reject models with undesireable properties such as the following:
 - Multiple objects: ex. http://sketchup.google.com/3dwarehouse/details?mid=ea7182868569cafa4e6c6248f210bd8b
 - Supporting geometry: ex. http://sketchup.google.com/3dwarehouse/details?mid=c8a32ee82a91795511fc2b865c2a185b
We somtimes accepted models that contained multiple objects, if the collection is also meaningful. Examples include:
 - Fruit bowl: http://sketchup.google.com/3dwarehouse/details?mid=c5a2f2b387962f95efa86b03d795ce7f
 - Rows of books: http://sketchup.google.com/3dwarehouse/details?mid=45e888388c36cace7c6ab6f4a65805ac

All files on Google 3D Warehouse are referenced using a unique model ID that is a hash of the model's SketchUp file and the user who uploaded it.
We use these hashes internally as well, so it is easy to recover information about a particular model from Google Warehouse.

<give approximate database size at each level here>

**** 2. Database Files

There are four folders in the database:
 - models: Contains Wavefront .obj files for all models, along with corresponding .mtl files.
 - textures: JPEG textures used by the .obj files.
 - scenes: Contains scene file descriptions for all files in the database.  Scenes come in two format, *.scs, which is used by SceneStudio, and *.txt, which is a simpler file format used by the code in this project.
 - fields: A list of the name and tags for each model, indexed by Google model ID.

 We provide three different databases:
 "databaseSample" contains a single scene and is meant for testing purposes (~11MB).
 "databaseObserved" contains all scenes users have modeled, but only those models in the database that occur in at least one scene (~2.7GB, uncompressed).
 "databaseFull" contains all scenes users have modeled, and all models in the model database (~20GB, uncompressed).

**** 3. Code Structure

This code all uses GLUT and is setup to compile on Windows with Visual Studio and several versions of Linux with gcc.
The project uses the "convert" program from ImageMagick to read *.jpg files; for Windows, we have included a statically linked version of this binary. Linux users will need to make sure convert is accessible.
Let us know you encounter any other trouble compiling the code on Linux or Windows.
There are two projects, modelViewer and sceneViewer.
These projects can be configured by modifying bin/parameters.txt.
Changing databaseDirectory can be used to switch between the "sample", "observed", and "full" databases.

sceneViewer -- this project reads the scene file specified by the "defaultScene" parameter.
It loads all the models in this scene and renders them using the transform specified in the scene file.

modelViewer -- this project can be used to browse the model database.
It loads all the model names and tags from the <database>/fields directory.
These models are sorted according to the "textQuery" parameter.
Use "textQuery=@" to specify a random order.
The left and right arrow keys browse through the list of results.

**** 4. Possible Uses

 - 
