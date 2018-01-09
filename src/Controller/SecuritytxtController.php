<?php

namespace Drupal\securitytxt\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\securitytxt\SecuritytxtService;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\Response;

/**
 * Controller routines for securitytxt routes.
 */
class SecuritytxtController extends ControllerBase {

    /**
     * The Securitytxt service.
     *
     * @var \Drupal\securitytxt\SecuritytxtService
     */
    protected $securitytxt;

    /**
     * Construct a new SecuritytxtController.
     *
     * @param \Drupal\securitytxt\SecuritytxtService
     *   The Securitytxt service.
     */
    public function __construct(SecuritytxtService $securitytxt) {
        $this->securitytxt = $securitytxt;
    }

    /**
     * {@inheritdoc}
     */
    public static function create(ContainerInterface $container) {
        return new static(
            $container->get('securitytxt.service')
        );
    }

    /**
     * Get the security.txt file as a response object.
     *
     * @return \Symfony\Component\HttpFoundation\Response
     *   The security.txt file as a response object with a content type of 'text/plain'.
     */
    public function securitytxtFile() {
        $content = $this->securitytxt->getSecuritytxtFile();
        $response = new Response($content, 200, ['Content-Type' => 'text/plain']);

        return $response;
    }

    /**
     * Get the security.txt.sig file as a response object.
     *
     * @return \Symfony\Component\HttpFoundation\Response
     *   The security.txt.sig file as a response object with a content type of 'text/plain'.
     */
    public function securitytxtSignature() {
        $content = $this->securitytxt->getSecuritytxtSignature();
        $response = new Response($content, 200, ['Content-Type' => 'text/plain']);

        return $response;
    }
}
