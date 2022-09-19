/* $fn = 100; */

sw_dist = 19;
sw_x = 14;
// keycap_x = 18;

sw_o = 4;
sw_os = [0, sw_o, sw_o * 2, sw_o * 2, sw_o * 2, sw_o, 0];

p_x = sw_dist * 7;
p_y = sw_dist * 6 + 2 * sw_o;

plate_total_z = 5;
/* plate_w = 1.5; */
/* pcb_z = 0.8; */

c_r = 2;
c_h = 0.5;

plate_z = 1.2;
plate_low_z = 1.3;
/* case_low_stack_z = 2; */
/* case_low_normal_z = 2.6; */
case_low_z = 1;
case_bottom_z = 1;

usb_x = 10;
usb_y = 16;
usb_z = case_low_z;

sw_x1 = 5;
sw_y1 = 1;

sw_lp_x1 = 4;
/* sw_lp_r = 0.2; */
sw_lp_x2 = 5;
sw_lp_y2 = 2;

module hole(di) {
    // 4 corner standoff hole
    for(x1 = [5, p_x - 5],  x2 = [sw_dist, p_x - sw_dist]) {
        for(i = [[x1, p_y - 5, 0], [x2, 5, 0]]) {
            translate(i) {
                cylinder(case_low_z, d = di);
            }
        }
    }
    
    // center hole
    /* *for(i = [0, 2, 4, 6], j = [2, 4]) { */
    /*     translate([sw_dist * (i + 0.5), sw_os[i] + sw_dist * j, 0]) cylinder(case_low_z, d = di); */
    /* } */
}

module plate0(x, y, z, r = c_r, center=false) {
  translate([r, r, 0]) minkowski() {
    cube([x - r * 2, y - r * 2, z - c_h]);
    cylinder(h = c_h, r = r);
  }
}

module plate(x, y, z, r = c_r, center=false) {
  if(center==true) {
    translate([-x / 2, -y / 2, 0]) {
      plate0(x, y, z, r, center);
    }
  } else {
    plate0(x, y, z, r, center);
  }
}


//color("Violet", 1) translate([-0.1,-0.3,1]) import("./pcb/sok42-B_Courtyard.svg");

module sw() {
    translate([0, 0, plate_total_z / 2]) cube([sw_x, sw_x, plate_total_z], true);
    for(i = [-sw_x / 2 - sw_y1, sw_x / 2])
        translate([-sw_x1 / 2, i, 0]) cube([sw_x1, sw_y1, plate_low_z]);
}


/* projection(cut = false) */
*translate([0, 0, 0]) {
    // plate
    translate([0, 0, plate_low_z])
    difference() {
        plate(p_x, p_y, plate_z, c_r);
        
        // sw
        for(i = [0 : 6]) {
            translate([0, sw_os[i], 0]) for(j = [0 : 5]) {
                translate([(i + 0.5) * sw_dist, (j + 0.5) * sw_dist, 0]) 
                    translate([0, 0, plate_total_z / 2]) cube([sw_x, sw_x, plate_total_z], true);
            }
        }

        hole(2);
    }
    
    // p1 plate low
    /* translate([0, 0, -plate_low_z]) */
    difference() {
      plate(p_x, p_y, plate_low_z, c_r);
        
        // sw
        for(i = [0 : 6]) {
            translate([0, sw_os[i], 0]) for(j = [0 : 5]) {
                translate([(i + 0.5) * sw_dist, (j + 0.5) * sw_dist, 0]) sw();
            }
        }
        
        hole(3.2);
        
        // front rgb
        /* for(i = [0 : 3]) translate([42.5 + i * 16, 4.5, 0]) */
        /*     cylinder(h = plate_low_z, r = rgb_r); */

        // usb
        usb_x1 = 4;
        for (i = [3 : 4]) {
          translate([sw_dist * i, p_y - 8 / 2, 0]) {
            translate([-usb_x / 2, 0, usb_z / 2]) cube([usb_x1, 8, usb_z], true);
            translate([usb_x / 2, 0, usb_z / 2]) cube([usb_x1, 8, usb_z], true);
          }
        }
        for (i = [2, 5]) {
          translate([sw_dist * i, p_y - 8 / 2, 0]) {
            translate([-usb_x / 2, 0, usb_z / 2]) cube([usb_x1, 8, usb_z], true);
            translate([usb_x / 2, 0, usb_z / 2]) cube([usb_x1, 8, usb_z], true);
          }
        }
    }
}


// p2 case edge frame pmma
/* projection(cut = false) */
translate([0, 0, case_bottom_z])
difference() {
    union() {
        difference() {
            // outside
          plate(p_x, p_y, case_low_z, c_r);
            
          // inside
          // switch cut out
          for(i = [0:5]) {
            // row
            translate([0, sw_dist * (i + 0.5), 0]) union() {
              for(j = [0:6]){
                translate([sw_dist * (j + 0.5), sw_os[j], 0]) {
                  cylinder(h = case_low_z, d = sw_lp_x1);
                  for(k = [-1, 1]){
                    translate([-sw_lp_x2/2, k * 6.5 - sw_lp_y2 / 2, 0])
                      cube([sw_lp_x2, sw_lp_y2, case_low_z]);
                  }
                  // verify
                  /* if(i == 5 && j == 3) echo (sw_dist * (j + 0.5), sw_dist * (i + 0.5) + sw_os[j], 0); */
                }
              }
            }
        }

            // mcus
            for (i = [3, 4]) {
              translate([sw_dist * i, sw_os[2] + sw_dist * 5, case_low_z / 2])
                cube([25, 12, case_low_z], true);
            }
            for (i = [3, 4]) {
              translate([sw_dist * i, sw_os[2] + sw_dist * 4.5 - 1.5, case_low_z / 2])
                cube([14, 7, case_low_z], true);
            }
            for(i = [2, 5]) {
              translate([sw_dist * (i + 0), sw_dist * 4.5 + sw_os[2], case_low_z / 2])
                cube([10, 8, case_low_z], true);
            }
            for(i = [2, 5]) {
              translate([sw_dist * (i + 0), sw_dist * 5 + sw_os[2], case_low_z / 2])
                cube([8, 5, case_low_z], true);
            }

            // usb
            for (i = [3 : 4]) {
              translate([sw_dist * i, p_y - usb_y / 2, 0]) {
                translate([0, 0, usb_z / 2]) cube([usb_x, usb_y, usb_z], true);
              }
            }
            for (i = [2, 5]) {
              translate([sw_dist * i, p_y - 10 / 2, 0]) {
                translate([0, 0, usb_z / 2]) cube([usb_x, 10, usb_z], true);
              }
            }

        }
    }

    // mos
    for (i = [0 : 6]) {
      translate([(i + 0.5) * sw_dist, 3 * sw_dist + sw_os[i], case_low_z /2]) {
        cube([10, 8, case_low_z], true);
      }
    }
    
    hole(3.2);
}


// p3 bottom plate
/* projection(cut = false) */
*difference() {
  plate(p_x, p_y, case_bottom_z, c_r);
  hole(2);
}
