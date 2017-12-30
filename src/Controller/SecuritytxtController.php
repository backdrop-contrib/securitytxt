<?php

namespace Drupal\securitytxt\Controller;

use Drupal\Core\Controller\ControllerBase;

class SecuritytxtController extends ControllerBase {

    public function securitytxtFile() {
        return array(
            '#markup' => 'my security.txt file',
        );
    }
}