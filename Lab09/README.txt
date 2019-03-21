Kameron Gill
Hasson Qayum

Help from MEP tutor- Chris
Battleboats - Lab9


In this lab, we create a replica of the popular game BattleShips. We have an
OLED screen on the Microcontroller that has the "ships" emulated. You then can
press buttons to guess a spot on the OLED and "shoot" down the enemy boat. I
think one of the most important parts of this lab was to create Protocol.c. This
handled all of the communication between the two microcontrollers.

For this Lab, We split up the work. I worked on Field.c, and my partner worked
on Protocol.c. We then tested them both indivually in tester.c. We then tested
them both using the HumanAgent.o file that was given to us. After we were fully
satisfied with testing, we then coded ArtificalAgent.c indivually. I worked on
AgentInit() and AgentGetStatus() and AgentGetEnemyStatus(). My partner worked on
AgentRun() and I will helped with any parts that needed Field.c functions since
I knew what to do.

So, We were able to get the game to appear on the microcontroller, however
agentInit() was broken in the sense that the boats would not all appear on the
board so we hardcoded their positions. We did not fully test AiAgent and are
missing parts of the FSM for it. I took about 7 hrs for Field.c and worked about
3 hrs on AiAgent. IMO, I wish we just stopped working on the lab after we got
Protocol/Field done since those are the bulk of the points. My partner worked
alot on AiAgent and I feel bad since we are going to get very little points out
of it.


The lab manual did not cover all of the knowledge to complete the lab and I had
to use my MEP tutor to further understand the lab.


