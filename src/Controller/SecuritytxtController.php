<?php

namespace Drupal\securitytxt\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\securitytxt\SecuritytxtService;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\Response;

class SecuritytxtController extends ControllerBase {

    protected $securitytxt;

    public function __construct(SecuritytxtService $securitytxt) {
        $this->securitytxt = $securitytxt;
    }

    public static function create(ContainerInterface $container) {
        return new static(
            $container->get('securitytxt.service')
        );
    }

    public function securitytxtFile() {
        $content = $this->securitytxt->getSecuritytxtFile();

        $response = new Response($content, 200, ['Content-Type' => 'text/plain']);

        return $response;
    }

    public function securitytxtSignature() {
        $content = 'This is security.txt.sig content.';
        $content = $this->securitytxt->getSecuritytxtSignature();

        $response = new Response($content, 200, ['Content-Type' => 'text/plain']);

        return $response;
    }
}