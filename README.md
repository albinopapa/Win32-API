# Win32-API
There are two solutions in this project, Win32 API and Win32 API Test.  
The Win32 API is just a few Win32 API wrappers in C++ and compiles to a .lib file.  
The Win32 API Test is a platformer game I'm creating as a test for the Win32 API lib.  

With the updated stuff from C++11/14 I've started making corresponding wrappers for the Win32 API.  Just a time killer waster really, but it keeps me interested in programming.  
It encompasses just creating a main window with WS_OVERLAPPEDWINDOW as it's style.  It's default size is 800x600.  The motivation for this project was looking at how Microsoft made their Direct2D API, which is a more recent API than the Win32API.  
In the Direct2D API, a lot of the functions have default parameters, which work most of the time as is.  I just thought if the Win32API was updated to be more like that and used some of the new C++ features like move semantics and std::unique_ptr, not aonly would it be a little more efficient, but also safer.  Combine that wil using parameter defaults that are known to work, perhaps it would be quicker and easier making Windows desktop applications.


The platformer is something I've wanted to do for a while now, but really never got around to making it.  There are so many things to learn about programming and code design, and game mechanics that I just think about how long it will take to make a fun game and get discouraged.  I'm taking it slow this time around and trying not to think about it, rather just do it.
