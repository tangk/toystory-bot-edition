# toystory-bot-edition

The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units.

The application can read commands from a file or stdin.

## Building

Clone repository:
<pre><code>$ git clone https://github.com/tangk/toystory-bot-edition</code></pre>

Execute at the root directory: <pre><code>$ cmake .
$ make</code></pre>

Tests are available at: toy-robot-tests directory

## Usage

Place commands in a file or input via stdin.

<pre><code>$ ./toy_robot input_file

$ ./toy_robot
PLACE 0,0,NORTH
MOVE
RIGHT
REPORT
0,1,EAST</code></pre>

Commands available:
<pre><code>PLACE X,Y,F
MOVE
LEFT
RIGHT
REPORT</code></pre>

**PLACE**
<p>PLACE will put the toy robot on the table in position X,Y and facing NORTH, SOUTH, EAST or WEST.
It is required that the first command to the robot is a PLACE command, after that, any sequence of commands may be issued, in any order, including another PLACE command.
The application will discard all commands in the sequence until a valid PLACE command has been executed.</p>

**MOVE**
<p>MOVE will move the toy robot one unit forward in the direction it is currently facing.</p>

**LEFT/RIGHT**
<p>LEFT and RIGHT will rotate the robot 90 degrees in the specified direction without changing the position of the robot.</p>

**REPORT**
<p>REPORT will announce the X,Y and F of the robot.</p>
