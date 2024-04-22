$fn = 20;

key_count = 4;
screw_holes = [[42, -55], [42, 75]];
pot_d = 24;
// pot_d = 6;
offset_d = 4;
// key_hole_size= 22;
key_hole_size= 14;
screw_hole_m2 = 2.5;
// screw_hole_m3 = 6.5;
screw_hole_m3 = 3.5;

module base() {
 translate([0, 10, 0]) square([90, 160], center = true);
}

// color([1, 0, 0, 0.5]) middle();
difference() {
	offset(offset_d * 0.9) base();
	top();
}

module top() {
	translate([0, 20 * key_count / 2 + 12, 0]) scale(15) projection() import("cbp.stl");
	translate([-20 * key_count / 2 + 10, -20 * key_count / 2 + 10, 0])
	// Key holes
	union() {
		for(i = [0 : key_count - 1]) {
			for(j = [0 : key_count - 1]) {
				translate([20 * i, 20 * j, 0])
					square(key_hole_size, center = true);
			}
		}
	}
	translate([0, -55, 0]) scale(5) projection() import("edge.stl");
	holes();
	translate([-20, -55, 0]) circle(d = pot_d);
	translate([20, -55, 0]) circle(d = pot_d);
	translate([0, 75, 0]) circle(d = pot_d);
	translate([-25, 75, 0]) circle(d = pot_d);
	translate([25, 75, 0]) circle(d = pot_d);
}

module holes() {
	// Screw holes
	// $fn = 6;
	for(i = [0 : len(screw_holes) - 1]) {
		translate([screw_holes[i][0], screw_holes[i][1], 0]) circle(d = screw_hole_m3);
		translate([-screw_holes[i][0], screw_holes[i][1], 0]) circle(d = screw_hole_m3);
	}
}
module bottom() {
	holes();
	translate([0, 10, 0]) pi_pico();
	translate([0, 90 + offset_d, 0]) type_c_hole();
}
module middle() {
	difference() {
		offset(offset_d * 1.1) base();
		offset(offset_d * -1.1) base();
		// translate([0, 90 + offset_d, 0]) type_c();
		holes();
	}
}
module pi_pico() {
	hole_offset_x = 11.4;
	hole_offset_y = 46;
	holes =
		[[hole_offset_x / 2, hole_offset_y / 2],
		 [hole_offset_x / 2, -hole_offset_y / 2],
		 [-hole_offset_x / 2, hole_offset_y / 2],
		 [-hole_offset_x / 2, -hole_offset_y / 2]];
	for (i = [0:len(holes) - 1]) {
		translate([holes[i][0], holes[i][1], 0]) circle(d = screw_hole_m2);
	}
}
module type_c_hole() {
	x_offset = 33;
	y_offset = 4.5;
	translate([-x_offset / 2, -y_offset, 0])
		circle(d = screw_hole_m2);
	translate([x_offset / 2, -y_offset, 0])
		circle(d = screw_hole_m2);
}
module type_c() {
	y_offset = 4.5;
	translate([0, -y_offset, 0])
		square([40, 10], center = true);
}
