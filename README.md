# Camera Transitions Research

This project was developed by [Ángel González J.]([https://www.linkedin.com/in/%C3%A1ngel-gonz%C3%A1lez-jim%C3%A9nez-147174196/?locale=es_ES](https://www.linkedin.com/in/ángel-gonzález-jiménez-147174196/?locale=es_ES)) , a second year student of the [Bachelor's degrees in Video Game Design and Development at CITM/TTC](<https://www.citm.upc.edu/ing/estudis/graus-videojocs/>) as of 31/03/2020. 

This content was generated for the Project II subject under the supervision of lecture [Ramón Santamaria](<https://www.linkedin.com/in/raysan/>).



## About this project

This research's goal was to produce a functional scene and transition system in C++.

You can visit the research's website [here](<https://barcinolechiguino.github.io/Camera-Transitions-Research/>). All the information related to the research can be found there.

The project contains 8 different transitions, including fades, wipes and zoom, all of which can be interpolated linearly and non-linearly as well as be modified to some degree. (Ex: Wipe can transition from all sides of the screen)



**Software used to develop this project:**

* [Visual Studio 2019](<https://visualstudio.microsoft.com/es/vs/?rr=https%3A%2F%2Fwww.google.com%2F>)
* [SDL](<https://www.libsdl.org/>) & [STL](<http://www.cplusplus.com/reference/stl/>) Libraries
* [Tiled](<https://www.mapeditor.org/>)
* [Online Converter](<https://www.onlineconverter.com/video-to-gif>)



## Test the project

Download the [release](<https://github.com/BarcinoLechiguino/Camera-Transitions-Research/releases>) and execute the Camera_Transitions_Research.exe. The available transitions options are:

* **LEFT CLICK:**  Move the camera to the mouse position. 
* **RIGHT CLICK:** Zoom to the mouse position transition to the next scene.
* **1 Key:** Cut Transition
* **2 Key:**  Fade In / Fade Out Transition.
* **3 Key:** Horizontal Slide Transition. 
* **4 Key:** Vertical Slide Transition.
* **5 Key:** Horizontal Wipe Transition.
* **6 Key:** Vertical Wipe Transition.
* **7 Key:**  Alternating Bars Transition.
* **8 Key:** Expanding Bars Transition.



* **Disclaimer:** All transitions starting from the Horizontal Slide Transition behave differently depending from which scene is being transitioned to: 

  * **All "Horizontal" Methods:**

    * **Transitioning from the first scene:** Transition from Left to Right.
    * **Transitioning from the second scene:** Transition from Right to Left.

  * **All "Vertical" Methods:**

    * **Transitioning from the first scene:** Transition from Top to Bottom.

    * **Transitioning from the second scene:** Transition from Bottom to Top.

      

  * **Both "Bars" Methods:** 

    * **Transitioning from the first scene:** Horizontal Bars.
    * **Transitioning from the second scene:** Vertical Bars.



## About Author

* [GitHub](<https://github.com/BarcinoLechiguino>)
* [LinkedIn]([https://www.linkedin.com/in/%C3%A1ngel-gonz%C3%A1lez-jim%C3%A9nez-147174196](https://www.linkedin.com/in/ángel-gonzález-jiménez-147174196))



## Relevant Links

#### **GIFS**

* [Basic Transitions GIFS: Cuts & Transitions 101 ](<https://www.youtube.com/watch?v=OAH0MoAv2CI>)
* [VG GIFS 1: Pokemon Red/Blue - Curiosities of battle transitions](<https://www.youtube.com/watch?v=YbDCXJ0xH2g>)
* [VG GIFS 2: Shaders Case Study - Pokémon Battle Transitions](<https://www.youtube.com/watch?v=LnAoD7hgDxw>)
* [VG GIFS 3: The Art of the JRPG Battle Transition - Desma](<https://www.youtube.com/watch?v=Bgx26kfXzlg>)



#### **Videos** 

* [Math for Game Programmers: Fast and Funky 1D Nonlinear Transformations](<https://www.youtube.com/watch?v=mr5xkf6zSzk>)

* [Timing Fight Woosh ~ Boredom Video](<https://www.youtube.com/watch?v=9RoHMNXE6YM>)
* [Transition References Video 1](<https://www.youtube.com/watch?v=BagcGilr5vc>)
* [Transition References Video 2](<https://www.youtube.com/watch?v=AxtjgdsvyLk&feature=youtu.be>)



#### **Documentation** 

* [Wikipedia: Film Transition](<https://en.wikipedia.org/wiki/Film_transition>)
* [Traditional Transitions References 1](<https://biteable.com/blog/tips/video-transitions-effects-examples/>)
* [Traditional Transition References 2](<https://www.mentalfloss.com/article/21028/5-film-transitions-worth-knowing>)
* [Traditional Transition References 3](<https://www.premiumbeat.com/blog/the-hidden-meaning-behind-popular-video-transitions/>)
* [VG Transition References Documentation 1](<http://www.davetech.co.uk/screentransitions>)
* [VG Transition References Documentation 2](<http://www.ibuprogames.com/2015/11/10/camera-transitions/>)

* [Linear Interpolation](<https://blog.bitbull.com/2019/11/13/a-lerp-smoothing-tutorial-and-example-code/>)
* [Non-Linear Interpolation](<https://gamedev.stackexchange.com/questions/14799/non-linear-interpolation>)

* [Easing Functions](<https://easings.net/en>)
* [Shaders](<https://www.webopedia.com/TERM/S/shader.html>)

