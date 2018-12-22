# Photo Editing Software (PES)

Photo Editing Software (PES) is a multifunctional photo editor with an intuitive user interface. Images can be imported from the file system or computer camera and can be edited using the app. User-defined text boxes or stickers can be overlaid on the canvas provided by the application. Furthermore, users can draw on the canvas using a pen tool. The modified image can be saved to the file system or shared it on social media like FB/IG.

This project is created for partial fufillment of the requirements of the course COMP 2012H Fall 2018. The repository was originally hosted privately in GitLab while developing.

### Building

Run qmake to generate the make file and use make to build the binary.

```
$ qmake
$ make
```

We have plans to package this as an Arch Linux PKGBUILD package. Stay tuned! :)

### Documentation

Documentation can be generated using doxygen.

```
$ doxygen
```

The resultant documentation is in the doc folder. Open `doc/html/index.html` to access its homepage.

### Acknowledgement

The emoji stickers are Twemoji v11.2. The toolbar icons are downloaded from flaticon.com
