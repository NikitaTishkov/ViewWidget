.. Youtube video info viewer documentation master file, created by
   sphinx-quickstart on Tue Jul 14 18:37:41 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Youtube video info viewer's documentation!
=====================================================


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   GetData

   JsonParser

   main

Main information
================

 **Short description**

  This software is created for tracking on Youtube video statistics such as: likes, dislikes and comments. The program is under development, so now it can only show video statistics by id without auto-updating

 **Project vision**

  In future it will be connected by user Google account and can track all channel and video statistics in real-time

 **Installation**

  Firstly you need to have curl, json-c and gtk3 external libraries on your Linux machine

  *Build & Run*
  For building go to root directory and type ``make`` via terminal
  Now you can run "Viewer": ``./vw``

  *Clean*
  If you want to clear all unnecessary files, run ``make clean``

  If you want to return to original state, run ``make tidy``

 **Using**

  It is pretty simple to use, in case of its incomplete state:(
  Copy any video id from youtube, for example:
      https://www.youtube.com/watch?v=vHiFxhPs2TQ

  Than copy video id(ex:*vHiFxhPs2TQ*) to special pole
  Press *Get info*




Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
