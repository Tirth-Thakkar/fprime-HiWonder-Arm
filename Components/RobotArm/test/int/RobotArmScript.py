
from fprime_gds.common.testing_fw import predicates

def test_robot_arm(fprime_test_api):
    """Test command CMD_NO_OP

    Test that CMD_NO_OP can be sent and return without and errors
    """
    #fprime_test_api.send_and_assert_command("CdhCore.cmdDisp.CMD_NO_OP")

    #RESET
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 0])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 90])
    #PICK UP BLOACK 1
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 180])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 130])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 0])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 130])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 5])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 45])
    #DROP BLOCK ONE
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 20])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 130])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 160])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 180])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 10])

    #SECTION 2 RESET
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 180])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 130])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 0])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 130])


    #PICK UP BLOCK TWO
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 140])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 140])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 15])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 45])


    #DROP BOX 2
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 130])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 5])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["CLAW", 180])

    #RESET
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["SHOULDER", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["BASE", 0])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["ELBOW", 90])
    fprime_test_api.send_and_assert_command("ArmPiMiniRobotArm.robotArm.SetPosition", ["WRIST", 90])
