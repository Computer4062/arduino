<p class="intro">TSTAR is a task managing device that has been made to manage tasks at a community level rather than
		at a personal level</p>
<p class="intro">At a personal level someone can just pull out a phone and set up multiple alarms and there it is a task manager</p>
<p class="intro">Isn't that the same thing that this task manager device does?</p>
<ul id="tips">
	<li>This is the perfect equipement if you are going on a camping trip and you want to create a scheduel</li>
	<li>The old fashened look of a physical task manager would make it even reliable for that kind of tasks</li>
	<li>If compiled into a box it is easy to carry arround making it great for outdoor trips</li>
	<li>With a physical task manager device like this one you can inform about new tasks to not only your self but to every one with you</li>
	<li>With a task manager app in a phone you can only inform yourself and this is specially true if you have no internet connectivity</li>
	<li>Where there is less access to a reliable source of electricity a battery powered device like this becomes useful</li>
	<li>This is simple to use(once you get familiar with the controls), there is no unwantedly complicated features</li>
	<li>The battery charge retainment qualities of a physical task manager are much greater than that of a phone</li>
	<li>This also comes into good use in a house hold</li>
	<li>Like when you have some household tasks to complete and you are sharing them with others in the house</li>
	<li>That is all personal things but can it be used in a professional environment</li>
	<li>For small groups working on projects it can be usefull to announce break times and so on</li>
</ul>

<p>24/07/2024</p>
<p>Problems encountered</p>
<ul>
	<li>I had packaged the entier circuit into a box</li>
	<li>Just now I also realized that when I set an alarm that is at AM time it does not work</li>
	<li>This occured previously as well and I thought I had fixed it at that time</li>
	<li>I also realized that when the Arduino program hits 64% dynamic memory or 73% program space the alarm functionality stops working</li>
	<li>I tested this out by initializing some empty strings</li>
	<li>I think this would work if I compared the currentTime string and the alarmTime string and then make the device ring if they are equal</li>
	<li>I also wanted to add other features like Settings and Time Recorder but this problem prevented me from adding them</li>
	<li>The device is also insanely big</li>
	<li>This is supposed to be very small and portable</li>
</ul>

<p>Future projects</p>
<ul>
	<li>For future projects I will try to limit the use of Strings and use char* when ever it can be used</li>
	<li>I will also be catiouse about memory usage since the Arduino chip has a limited memory capacity</li>
	<li>I also think I should try to implement additional functionality using a Internet connection chip that would allow me to send http requests to webservers</li>
	<li>I would also learn to make webservers and intergrate both webserver and arduino together</li>
	<li>The project also looks like a vehicle so Iam thinking of building a housecleaning robot or something like that</li>
	<li>It would be great to have such a robot in a house where the robot can clean and access the internet to be intergrated with ChatGPT/Bard or other webservers</li>
	<li>This would give it functionalities like voice recognition and image recognition, Task management, Playing songs, Reciepies, Manuals, Internet surfing, Calculations</li>
	<li>In order to achieve this I believe I must learn how to make PCB's</li>
</ul>