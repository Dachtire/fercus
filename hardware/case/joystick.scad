$fn=100;

sw_x = 14;

sw_out_x = sw_x + 2;
sw_out_z = 3;
sw_out_cutin_x = sw_x - 4;

sw_plate_z = 1.2;
sw_plate_low_z = 2.5;
sw_plate_low_cutin_x = sw_x - 2;
sw_plate_low_cutin_z = 1;

js_y = 2;
js_down_z = 11.85;
js_up_z = 10.25;
js_down_hole_z = 9.95;
js_up_hole_z = 8.45;
js_offset0_z = 5 + 3;
js_offset1_z = js_offset0_z + 5;
js_z = js_offset1_z + js_down_z + js_up_z;
//js_plate_low_z = sw_plate_low_z - sw_plate_low_cutin_z;
js_hole_d = 2.5;

sw_snap_x = 5;
sw_snap_y = 1;
sw_snap_z = sw_plate_low_z - sw_plate_z;

space_x = 17;

//plate_r = 1;
//plate_h = 0.5;

//module plate(x, y, z, r = plate_r) {
//    minkowski() {
//        cube([x - r * 2, y - r * 2, z - plate_h], true);
//        cylinder(h=plate_h, r = r, center=true);
//    }
//}

//%plate(10, 10, 2);

module prism(x, y, z){
  polyhedron(
             points=[[-x/2,0,0], [x/2,0,0], [x/2,0,z], [-x/2,0,z], [-x/2,-y,z], [x/2,-y,z]],
             faces=[[0,1,2,3],[5,4,3,2],[0,4,5,1],[0,3,4],[5,2,1]]
  );
}

//for(i = [0:1]) translate([space_x * i, 0, 0]) 
difference() {
  union() {
    //    joystick mount plate
    translate([0, sw_x / 2 - 1, 0]) {
      difference() {
        translate([0, 0, js_z / 2]) cube([sw_out_x, js_y, js_z], true);
        
        // z hole alps
//        alps_down_hole_z = 8.35;
//        alps_up_hole_z = 7.9;
//        alps_hole_d = 2;
//        alps_hole_space = 2.5;
//        alps_mount_space_x = 12.65 / 2;
//        alps_mount_space_z = 10 / 2;
//        alps_mount_hole_d = 2.5;
//        alps_sw_hole_space_z = 4.5 / 2;
//        alps_sw_hole_space_x = 6.5 / 2;
//        // output pin
//        for(i = [-1:1]) {
//            translate([i * alps_hole_space, 0, js_offset_z + js_down_z + alps_down_hole_z + sw_out_z]) rotate([90, 0, 0]) cylinder(h = js_y, d = alps_hole_d, center = true);
//        }
//        for(i = [-1:1]) {
//            translate([alps_down_hole_z, 0, js_offset_z + js_down_z + sw_out_z + i * alps_hole_space]) rotate([90, 0, 0]) cylinder(h = js_y, d = alps_hole_d, center = true);
//        }
//        // switch pin
//        for(i = [-1,1], j = [-1,1]) { 
//        translate([i * alps_sw_hole_space_x, 0, js_offset_z + js_down_z + sw_out_z + j * alps_sw_hole_space_z - alps_up_hole_z]) rotate([90, 0, 0]) cylinder(h = js_y, d = alps_hole_d, center = true);
//        }
//        // mount pin
//        for(i = [-1,1], j = [-1,1]) { 
//        translate([i * alps_mount_space_x, 0, js_offset_z + js_down_z + sw_out_z + j * alps_mount_space_z]) rotate([90, 0, 0]) cylinder(h = js_y, d = alps_mount_hole_d, center = true);
//        }
      }
    }

    // joystick mount plate font strength
    js_side_y = sw_x;
    js_side_x = (sw_out_x - sw_x) / 2;
    difference() {
        for(i = [-1,1]) translate([i * (sw_x + js_side_x) / 2, -js_side_y / 2 - js_y, 0]) rotate([-90, 0, 0]) prism(js_side_x, js_z, js_side_y); 
        translate([0, -sw_out_x, 0]) cube([sw_out_x, sw_out_x, sw_out_x], true);
    }
    // joystick mount plate back strength
    js_back_y = 2;
    for(i = [-1, 1]) translate([i * sw_x / 2, (sw_out_x - js_back_y) / 2, js_z / 2]) cube([js_back_y, js_back_y, js_z], true);
    translate([0, (sw_out_x - js_back_y) / 2, js_z / 2]) cube([js_back_y * 2, js_back_y , js_z], true);

    
    //    z plate upper
    translate([0, 0, sw_out_z / 2]) difference() {
      cube([sw_out_x, sw_out_x, sw_out_z], true);
      cube([sw_out_cutin_x, sw_out_cutin_x, sw_out_z], true);
    }
    
    //    z plate, plate lower
    translate([0, 0, -sw_plate_low_z / 2]) difference() {
      cube([sw_x, sw_x, sw_plate_low_z], true);
      cube([sw_out_cutin_x, sw_out_cutin_x, sw_plate_low_z], true);
      translate([0, 0, sw_plate_low_cutin_z / 2 -sw_plate_low_z / 2]) cube([sw_plate_low_cutin_x, sw_plate_low_cutin_x, sw_plate_low_cutin_z], true);
    }

    // snap
    for(i = [0:4]) {
      rotate([0, 0, 90 * i]) translate([0, -sw_x / 2, -sw_snap_z - sw_plate_z]) prism(sw_snap_x, sw_snap_y, sw_snap_z);
    }
  }

  // plate upper snap cut
  sw_plate_up_snap_cut_y = (sw_out_x - sw_x) / 2;
  sw_plate_up_snap_cut_z = 1;
  for(i = [0:4]) {
  rotate([0, 0, 90 * i]) translate([0, -sw_out_x / 2 + sw_plate_up_snap_cut_y / 2, sw_plate_up_snap_cut_z / 2]) cube([sw_snap_x, sw_plate_up_snap_cut_y, sw_plate_up_snap_cut_z], true);
  }

  // snap cut
  sw_snap_cut_x = 0.2;
  sw_snap_cut_z = sw_plate_low_z + sw_plate_up_snap_cut_z;
  for(i = [-1, +1], j = [0, 1]) {
    rotate([0, 0, j * 90]) {
      translate([i * sw_snap_x / 2 - i * sw_snap_cut_x / 2, 0, - sw_plate_low_z + sw_snap_cut_z / 2]) cube([sw_snap_cut_x, sw_out_x, sw_snap_cut_z], true);
      translate([0, 0,  - sw_plate_low_z + sw_snap_cut_z / 2]) cube([sw_snap_x, sw_plate_low_cutin_x, sw_snap_cut_z], true);
    }
  }
  
    // plate z hole
    for (i = [js_offset0_z, js_offset1_z], j = [-js_down_hole_z, js_up_hole_z]) {
        translate([0, sw_x / 2 - 1, i + j + js_down_z]) rotate([90, 0, 0]) cylinder(h = 5, d = js_hole_d, center = true);
    }
}

// connection
*for(i = [0:2]) translate([space_x * (i + 0.5), sw_x / 2 - 1, js_z / 2]) rotate([0, 90, 0]) cylinder(d = 2, h = 1, center = true);
