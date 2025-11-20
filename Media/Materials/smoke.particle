particle_system smokeParticle{
    billboard_type point
    particle_width 35
    particle_height 35
    quota 500
    material smoke

    emitter Point {
        emission_rate 40
        direction 0 1 0
        velocity 20
        velocity_min 10
        velocity_max 30
        colour_range_start 0.6 0.6 0.6
        colour_range_end 0.2 0.2 0.2
        time_to_live_min 1.5
        time_to_live_max 3
    }

    affector ColourFader {
        red -0.2
        green -0.2
        blue -0.2
        alpha -0.3
    }

    affector Scaler {
        rate 50
    }

    affector ColourImage {
        image smokecolors.png
    } 
    
    affector Rotator {
        rotation_speed_range_start -30
        rotation_speed_range_end 55
        rotation_range_start 0
        rotation_range_end 18
    }
    
    affector DirectionRandomiser {
        randomness 5
    }
}
