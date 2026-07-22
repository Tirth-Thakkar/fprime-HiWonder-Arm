module Components {
    @ HiWonder Robotic Arm Driver for tabletop robotic arm.
            
        # Data types for arm
        struct JointAngle {
            baseRad: F64,
            shoulderRad: F64,
            elbowRad: F64,
            wristRad: F64,
            durationMs: U32
        }

        # Claw Position
        enum ClawPosition {
            OPEN = 0,
            CLOSE = 1
        }

        struct ClawState {
            position: ClawPosition,
            durationMs: U32
        }

        # Port Types
        port JointAnglePort(value: JointAngle)
        
        port ClawStatePort(value: ClawState)
    
    state machine HiWonderRoboticArmStateMachine {
        
        state IDLE {}

        state DISPATCHED {}

        state EXECUTING {}
    }


    active component HiWonderRoboticArm {

        async command TODO opcode 0

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

    }
}