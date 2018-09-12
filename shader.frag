#version 150

uniform float time;
uniform vec2 resolution;
uniform sampler2DRect tex;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);

  float count = 0.0;
  for(float x = -1.0; x <= 1.0; x++){

    for(float y = -1.0; y <= 1.0; y++){

        float r = texture(tex, texCoordVarying + vec2(x, y)).r;
        if(r == 1.0){
          count++;
        }
    }
  }

  float my = texture(tex, texCoordVarying).r;
  float next;
  if(my == 0.0){
    if(count == 2){
      next = 1.0;
    }else{
      next = 0.0;
    }
  }else if(my == 1.0){
    next = 0.5;
  }else if(my == 0.5){
    next = 0.0;
  }

  outputColor = vec4(vec3(next, next, 0.0), 1.0);
}
