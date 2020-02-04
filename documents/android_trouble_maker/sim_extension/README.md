# Kibo-RPC SimExtMod
This directory contains files to extend Astrobee simulator for Kibo-RPC.

## How to use
Please run bellow code in this directory.

``` sh
chmod +x setup.sh
./setup.sh
```

Then, launch Astrobee Simulator.

``` sh
launch astrobee sim.launch dds:=false robot:=sim_pub rviz:=true world:=iss
```

If the camera images are incorrect, it can be because the simulator cannot keep up.
Then the speed of simulation can be decreased, for example, try bellow.

``` sh
launch astrobee sim.launch dds:=false robot:=sim_pub rviz:=true world:=iss speed:=0.5
```

If Astrobee is not stable, run bellow code at another terminal and restart rviz.

``` sh
run executive teleop_tool -reset_bias
```

## Reference
1. 1st Kibo Robot Programming Challenge Programming manual chapter 4.5.7
