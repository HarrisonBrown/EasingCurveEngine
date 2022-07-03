# Curves
* All have the same parameters
  * x_t0
  * x_tmax
  * duration
* A simple(?) function for each to return the result at time t
  * Linear: y = mx + c
    * **y = (((tmax - t0) / duration) * x) + t0**
    * f(t) = x_t0 + t * (x_tmax - x_t0) / d
  * Quadratic: y = ax^2 + bx + c
    * InQuad
      * Vertex always 0,x_t0, passes through duration,x_tmax
      * y = a(x - h)^2 + k
      * y = a(x - 0)^2 + x_t0
      * x_tmax = a(duration - 0)^2 + x_t0
      * Solve for a
        * a = (x_tmax - x_t0) / duration^2
      * **y = ((x_tmax - x_t0) / duration^2) * x + x_t0**
    * OutQuad
      * Vertex always (duration, x_tmax), passes through 0,x_t0
      * y = a-(X - duration)^2 + x_tmax
      * x_t0 = a * -(0 - duration)^2 + x_tmax
      * Solve for a
        * a = (x_t0 - x_tmax) / -duration^2
      * **y = ((x_t0 - x_tmax) / -duration^2)-(X - duration)^2 + x_tmax**
  * InOutQuad: combo of above based on half the duration and x_tmax?

# Input Parsing
* Two forms of input, curve definition and query
* Query
  * Just a float, nothing else
* Curve definition 
  * Contain valid curve type (must be first?)
  * Contain three of "parameter=value"
    * Will future curve types have more parameters? Bezier curves?
  * Each parameter set only once
    * x_t0
    * x_tmax
    * duration

# Architecture
## Main
* Take input
* Split input into individual commands, delimited by line breaks
* For each input line
  * Call Validity checker
    * Takes input line as string
    * Returns code
      * good curve definition
      * good query 
      * not enough parameters for curve
      * per parameter
        * no '=' but not float
        * multiple '='
        * not valid parameter name
        * not valid value
  * Good code?
    * Create curve query engine object
      * Curve input?
        * Extract parameters and pass to query engine
      * Query input
        * Call engine query function

## Engine
* Stores latest curve parameters
* Holds functions for each curve type
  * Each Called from public Query() function which decides which to call based on stored curve params
    * Takes float t
    * returns int 

# Tests
* Test validator input
  * Each error code
* Test curve generator
  * Get expected value
  * Out of bound inputs